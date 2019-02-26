// This program is a part of NT MudLIB

#include <ansi.h>

inherit ROOM;

#define PROCEDURE_FUND  0.01            // 1/100 的手續費
#define STOCK_VALUE     10000           // 一張股票價值

varargs string stockvalue_change_description(float change, string type)
{
        string bgcolor;

        switch(type)
        {
                case "t3g2":
                        bgcolor = BGRN;
                        break;

                case "t3r2":
                        bgcolor = BRED;
                        break;
                default:
                        bgcolor = "";
                        break;
        }

        change = to_float(change);

        if( change > 0 )
                return bgcolor+sprintf(HIR"▲%5.2f", change);
        else if( change < 0 )
                return bgcolor+sprintf(HIG"□%5.2f", -change);
        else
                return bgcolor+sprintf(HIW"  %5.2f", change);
}


int do_liststock(string arg)
{
        int count;
        mapping stocks = STOCK_D->query_stocks();
        string *stock_sort = sort_array(keys(stocks), 1);
        mapping data;
        int min, max;
        string *msg = allocate(0);
        //float percent = PROCEDURE_FUND - me->query_skill("stock", 1)/10000.;
        float percent = 0.01;
        object me = this_player();

        if( arg )
        {
                if( sscanf(arg, "%d %d", min, max) != 2 )
                        sscanf(arg, "%d", min);
        }

        msg = ({"代號    股票名稱     現價    漲跌  漲跌幅度 開盤價 最高價 最低價 成交張數 \n"});
        msg += ({"—————————————————————————————————————————————\n"});

        foreach(string stock in stock_sort)
        {
                count++;

                if( max )
                {
                        if( to_int(stock) < min || to_int(stock) > max ) continue;
                }
                else
                {
                        if( min && to_int(stock) != min ) continue;
                }

                data = stocks[stock];

                if( !data["股票名稱"] ) continue;

                msg += ({sprintf(HIM"%-6s"HIW"  %-8s "HIY"%8.2f"NOR" %-8s %7.2f%% "NOR WHT"%6.2f "HIB"%6.2f %6.2f  "NOR BYEL HIY"%d\n"NOR,
                        stock,
                        data["股票名稱"],
                        data["現價"],
                        stockvalue_change_description(data["漲跌"], data["狀態"]),
                        data["漲跌幅"],
                        data["開盤"],
                        data["最高"],
                        data["最低"],
                        data["成交張數"],
                )});
        }
        msg += ({"—————————————————————————————————————————————\n"});
        msg += ({MAG"共 "HIM+count+NOR MAG" 只上市股票，"YEL"股票單位為 "HIY"1"NOR YEL" 兩黃金/張，"NOR RED"交易手續費為 "HIR+sprintf("%.2f%%", percent*100.)+NOR RED"。\n"NOR});
        msg += ({HIK"股票數據資料來自滬深A股，10分鐘更新一次，本次更新時間："+sprintf("%s\n", TIME_D->replace_ctime(STOCK_D->query_last_update_time()))+NOR});
        me->start_more(implode(msg, ""));
        return 1;
}

void confirm_buystock(object me, string num, int totalcost, int new_amount, float new_value, float cur_value, int amount, string stock_name, string arg)
{
        int td;

        if( !arg )
                return me->finish_input();

        arg = lower_case(arg);

        if( arg != "y" && arg != "yes" )
        {
                tell_object(me, "取消購入股票。\n");
                return me->finish_input();
        }

        if( query("balance", me)<totalcost )
        {
                tell_object(me, "你在銀行的錢不足。\n");
                return me->finish_input();
        }

        if( STOCK_D->query_get_stock_flag() )
        {
                tell_object(me, "股票資料更新中，請稍後再進行交易。\n");
                return me->finish_input();
        }

        td = time() / 86400;

        set("stock/"+num+"/amount", new_amount, me);
        set("stock/"+num+"/value", new_value, me);

        if( query("stock/"+num+"/limit/which_day", me) != td )
        {
                set("stock/"+num+"/limit/amount", amount, me);
                set("stock/"+num+"/limit/which_day", td, me);
        }
        else
        {
                addn("stock/"+num+"/limit/amount", amount, me);
        }

        CHANNEL_D->channel_broadcast("stock", me->query_idname()+RED"以 "HIY+sprintf("%.2f", cur_value)+NOR RED" 股價購入「"HIW+stock_name+NOR RED"」股票 "+amount+" 張。"NOR);
        tell_object(me, "交易完成。\n");
        me->finish_input();

        addn("balance", -totalcost, me);
        //TOP_D->update_top_rich(me);
        me->save();
}

int do_buystock(string arg)
{

        mapping stocks = STOCK_D->query_stocks();
        string num;
        int amount;
        float old_value;
        float new_value;
        float cur_value;
        int old_amount;
        int new_amount;
        int cost;
        int cost_extra;
        int *nowtime = TIME_D->query_realtime_array();
        float percent;
        object me = this_player();

        //tell_object(me, "股票系統目前無法處理重新掛牌、除權、除息等問題，風險自負。\n");

        if( !wizardp(me) && (/*nowtime[2] < 1 || nowtime[2] > 6 ||*/ nowtime[1] < 9 || nowtime[1] >= 22) )
        {
                tell_object(me, "週一至週日的早上九點至晚上十點允許交易。\n");
                return 1;
        }

        if( STOCK_D->query_last_update_time() < time() - 48*60*60 )
        {
                tell_object(me, "股票資料尚未更新，無法進行交易。\n");
                return 1;
        }

        if( STOCK_D->query_get_stock_flag() )
        {
                tell_object(me, "股票資料更新中，請稍後再進行交易。\n");
                return 1;
        }

        if( !arg || sscanf(arg, "%s %d", num, amount) != 2 )
        {
                tell_object(me, "請輸入正確的格式，例：buy 000002 100。\n");
                return 1;
        }

        if( amount < 1 )
        {
                tell_object(me, "你至少必須購買一張股票。\n");
                return 1;
        }

        if( !mapp(stocks[num]) || !stocks[num]["股票名稱"] )
        {
                tell_object(me, "沒有 "+num+" 這一隻股票。\n");
                return 1;
        }

        if( stocks[num]["狀態"] == "t3r2" )
        {
                tell_object(me, "這檔股票已經漲停，無法再買了。\n");
                return 1;
        }

        old_amount=query("stock/"+num+"/amount", me);
        new_amount = amount + old_amount;


        if( new_amount > 10000000 )
        {
                tell_object(me, "每隻股票最多隻能購買 10,000,000 張。\n");
                return 1;
        }

        old_value=to_float(query("stock/"+num+"/value", me));
        cur_value = stocks[num]["現價"];
        new_value = (old_value * old_amount + cur_value * amount) / (amount + old_amount);

        //percent = PROCEDURE_FUND - me->query_skill("stock", 1)/10000.;
        percent = 0.01;

        cost = to_int(to_int(cur_value*100) * STOCK_VALUE * amount / 100);
        cost_extra = to_int(cost * percent);

        if( cost + cost_extra < 1 )
        {
                tell_object(me, "資料計算錯誤，請通知巫師處理。\n");
                return 1;
        }

        tell_object(me,
                WHT"股票名稱      "NOR HIW+num+" "+stocks[num]["股票名稱"]+NOR"\n"
                "———————————————————\n"
                YEL"股票現在價格  "HIY+sprintf("%.2f", cur_value)+"\n"NOR
                GRN"欲購股票張數  "HIG+amount+"\n"NOR
                GRN"目前持股價格  "HIG+sprintf("%.2f", old_value)+"\n"NOR
                GRN"目前持股張數  "HIG+old_amount+"\n"NOR
                CYN"平均之後價格  "HIC+sprintf("%.2f", new_value)+"\n"NOR
                CYN"欲購股票總值  "HIC+cost+"\n"NOR
                CYN"交易手續費用  "HIC+cost_extra+HIR"("+sprintf("%.2f", percent*100.)+"%)\n"NOR
                CYN"購入總共花費  "HIC+(cost + cost_extra)+"\n"NOR
                "———————————————————\n"
                HIY"是否確定購入股票?"NOR YEL"(Yes/No)"NOR
        );

        input_to((: confirm_buystock, me, num, cost + cost_extra, new_amount, new_value, cur_value, amount, num+" "+stocks[num]["股票名稱"] :));
        return 1;
}

void confirm_sellstock(object me, string num, int totalearn, int new_amount, float old_value, float cur_value, int amount, string stock_name, string arg)
{

        if( !arg )
                return me->finish_input();

        arg = lower_case(arg);

        if( arg != "y" && arg != "yes" )
        {
                tell_object(me, "取消販賣股票。\n");
                return me->finish_input();
        }

        if( STOCK_D->query_get_stock_flag() )
        {
                tell_object(me, "股票資料更新中，請稍後再進行交易。\n");
                return me->finish_input();
        }

        if( new_amount <= 0 )
                delete("stock/"+num, me);
        else
                set("stock/"+num+"/amount", new_amount, me);

        if( cur_value == old_value )
                CHANNEL_D->channel_broadcast("stock",
                        me->query_idname()+RED"以 "HIY+sprintf("%.2f", cur_value)+NOR RED" 股價售出「"HIW+stock_name+NOR RED"」股票 "+amount+" 張。"NOR);
        else if( cur_value > old_value )
                CHANNEL_D->channel_broadcast("stock",
                        me->query_idname()+RED"以 "HIY+sprintf("%.2f", cur_value)+NOR RED" 股價售出「"HIW+stock_name+NOR RED"」股票 "+amount+" 張，獲利 "
                        HIY+to_int(to_int((cur_value-old_value)*100)*STOCK_VALUE/100*amount)+NOR RED"。" NOR);
        else
                CHANNEL_D->channel_broadcast("stock",
                        me->query_idname()+RED"以 "HIY+sprintf("%.2f", cur_value)+NOR RED" 股價售出「"HIW+stock_name+NOR RED"」股票 "+amount+" 張，認賠 "
                        HIY+to_int(to_int((old_value-cur_value)*100)*STOCK_VALUE/100*amount)+NOR RED"。" NOR);
        tell_object(me, "交易完成。\n");

        me->finish_input();

        addn("balance", totalearn, me);
        //TOP_D->update_top_rich(me);
        me->save();
}

int do_sellstock(string arg)
{
        mapping stocks = STOCK_D->query_stocks();
        string num;
        int amount;
        int old_amount;
        int new_amount;
        float cur_value;
        float old_value;
        int earn, td, limit = 0;
        int *nowtime = TIME_D->query_realtime_array();
        object me = this_player();

        if( !wizardp(me) && (/*nowtime[2] < 1 || nowtime[2] > 6 ||*/ nowtime[1] < 9 || nowtime[1] >= 22) )
        {
                tell_object(me, "週一至週日的早上九點至晚上十點允許交易。\n");
                return 1;
        }

        if( STOCK_D->query_last_update_time() < time() - 48*60*60 )
        {
                tell_object(me, "股票資料尚未更新，無法進行交易。\n");
                return 1;
        }

        if( STOCK_D->query_get_stock_flag() )
        {
                tell_object(me, "股票資料更新中，請稍後再進行交易。\n");
                return 1;
        }

        if( !arg || sscanf(arg, "%s %d", num, amount) != 2 )
        {
                tell_object(me, "請輸入正確的格式，例：sell 000002 100。\n");
                return 1;
        }

        if( amount < 1 )
        {
                tell_object(me, "你至少必須出售一張股票。\n");
                return 1;
        }

        if( !mapp(stocks[num]) || !stocks[num]["股票名稱"] )
        {
                tell_object(me, "沒有 "+num+" 這一隻股票。\n");
                return 1;
        }

        if( stocks[num]["狀態"] == "t3g2" )
        {
                tell_object(me, "這檔股票已經跌停，無法再賣了。\n");
                return 1;
        }

        td = time() / 3600;

        old_amount=query("stock/"+num+"/amount", me);

        // 當天購買的股票不可以賣出
        if( query("stock/"+num+"/limit/which_day", me) == td )
                limit=query("stock/"+num+"/limit/amount", me);

        new_amount = old_amount - amount;

        old_value=to_float(query("stock/"+num+"/value", me));
        cur_value = stocks[num]["現價"];

        if( old_amount < 1 )
        {
                tell_object(me, "你手上並沒有 "+num+" 這隻股票。\n");
                return 1;
        }

        if( new_amount < limit )
        {
                tell_object(me, "這隻股票你手上只有 "+old_amount+" 張，可交易 "+(old_amount-limit)+" 張。\n");
                return 1;
        }

        earn = to_int(to_int(cur_value*100) * amount * STOCK_VALUE / 100);

        if( earn < 1 )
        {
                tell_object(me, "資料計算錯誤，請通知巫師處理。\n");
                return 1;
        }

        tell_object(me,
                WHT"股票名稱      "NOR HIW+num+" "+stocks[num]["股票名稱"]+NOR"\n"
                "———————————————————\n"
                YEL"股票現在價格  "HIY+sprintf("%.2f", cur_value)+"\n"NOR
                GRN"目前持股價格  "HIG+sprintf("%.2f", old_value)+"\n"NOR
                GRN"目前持股利潤  "HIG+sprintf("%.2f%%", (cur_value - old_value) * 100. / old_value)+"\n"NOR
                GRN"欲售股票張數  "HIG+amount+"\n"NOR
                CYN"售出總共獲得  "HIC+earn+"\n"NOR
                "———————————————————\n"
                HIY"是否確定售出股票?"NOR YEL"(Yes/No)"NOR
        );

        input_to((: confirm_sellstock, me, num, earn, new_amount, old_value, cur_value, amount, num+" "+stocks[num]["股票名稱"] :));
        return 1;
}

void create()
{
        set("short", "證券交易所");
        set("long", @LONG
這是一家證券交易所，牆上掛着一個牌子(paizi)。
LONG );

        set("item_desc", ([
                "paizi" : @HELP
顯示股市資訊
liststock              列出所有滬深A股市場資料
liststock 000002       列出代號000002股票的資料
buystock 000002 300    買入000002股票300張
sellstock 000002 100   賣出000002股票100張
istock                 列出自己購買的股票資料

HELP,
        ]));
        set("exits", ([
                "south": __DIR__"kedian",
        ]));
        set("no_fight", 1);
        set("coor/x", 20);
        set("coor/y", 0);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_liststock", "liststock");
        add_action("do_buystock", "buystock");
        add_action("do_sellstock", "sellstock");
}