// warehouse.c
// Updated by Lonely

#define IN_OUT_RATE     80/100
#define BUSI_SAVE_DIR   "/data/business/"
#define MAX_TRADE       20000000 // 每筆最大的貿易額為 2 千萬兩白銀
#undef IN_TEST

#include <ansi.h>

inherit F_SAVE;
inherit ROOM;
#include <price.h>

class ware
{
        string name;    /* 中文名字 */
        string id;      /* id */
        int value;      /* 當前單價(單位：銀子) */
        int o_value;    /* 初始價格 */
        int amount;     /* 當前保有數量 */
        int o_amount;   /* 初始數量 */
        string unit;    /* 單位 */
}

nomask protected int valid_check();
nomask protected void init_wares();
nomask protected void get_shougou_amount(string arg,object me,class ware w);
nomask protected void get_paochu_amount(string arg,object me,class ware w);
nomask protected void output_list(string number,object who);
nomask protected string list_one_kind(string kind);
string query_save_file()
{ return sprintf("%s%s_bsave",BUSI_SAVE_DIR,domain_file(file_name(this_object())));}

mapping all_wares = ([]);
nosave int no_trade = 0;

int system_change = 0;  // 供系統調整用。change 的單位為黃金.

nosave int price_rate = 100;

// 恢復調整
// {
nosave int change_max = 20000000; /* silver */
nosave string *changed_class = ({});
// }

nomask int query_price_rate()
{
        return price_rate;
}

nomask varargs protected void do_count(string name,int silver)
{
        int i,n,change;
        int orig, cha;
        int rate;
        string domain,*kinds = keys(all_wares);

        n = sizeof(kinds);
        for(i=0;i<n;i++)
        {
                foreach(class ware oneitem in all_wares[kinds[i]])
                {
                        orig += oneitem->o_value * oneitem->o_amount; /* silver數 */
                        cha += (oneitem->o_amount -  oneitem->amount)*oneitem->o_value;
                }
        }

        rate = (cha+(system_change*100))/(orig/100);

        if(rate < -50)
                rate = -50;
        else if(rate > 50)
                rate = 50;

        if(stringp(name) && silver && (abs(silver) >= orig/100))
        {
                domain = to_chinese(domain_file(file_name(this_object())));
                change = abs((100+rate) - price_rate);

                if(change >= 5)
                {
                        if(silver > 0)
                                CHANNEL_D->do_channel( this_object(), "news",
                                        sprintf("聽說由于有人在%s大量收購%s致使當地物價飛漲。\n",domain,name));
                        else
                                CHANNEL_D->do_channel( this_object(), "news",
                                        sprintf("聽說由于有人在%s大量拋售%s致使當地物價飛速下滑。\n",domain,name));
                }
                else if(change >= 1)
                {
                        if(silver > 0)
                                CHANNEL_D->do_channel( this_object(), "news",
                                        sprintf("聽說由于有人在%s大量收購%s致使當地物價有所上揚。\n",domain,name));
                        else
                                CHANNEL_D->do_channel( this_object(), "news",
                                        sprintf("聽說由于有人在%s大量拋售%s致使當地有所下降。\n",domain,name));
                }
        }

        price_rate = 100 + rate;
}

// 此物件應受到最嚴格的檢查。
nomask protected int valid_check()
{

        string fname,domain;
        int idx;

        if(clonep())
                return 0;
        if(!sscanf((fname = file_name(this_object())),"/d/%*s"))
                error("商棧物件必須存在于區域目錄下。\n");
        idx = strsrch(fname, "/", -1);
        if(fname[idx+1..] != "business")
                error("商棧物件的文件名必須是'business'。\n");

        sscanf(fname,"/d/%s/business",domain);

        if(member_array(domain,BUSINESS_D->query_valid_domains()) == -1)
                error("此區域目前為非貿易區域，如需通商請向神申請。\n");

        return 1;
}

nomask void setup()
{
        if(!valid_check())
                return;

        if(!restore())
                init_wares();
        else
                do_count();
        set("channel_id", "商會");
        set("no_clean_up",1);
        ::setup();
}

nomask protected void init_wares()
{
        mapping wares = query("all_wares");
        mapping kinds = query("kind_rate");
        string *items;
        string kind;
        int i,n;

        items =  filter_array(explode(PRICES, "\n") - ({ "" }), (: $1[0] != '#' :));

        if(!items || !(n=sizeof(items)))
                return;

        for(i=0;i<n;i++)
        {
                class ware item;
                string name,id,unit;
                int value;

                if(sscanf(items[i],"%s %s %s %d",name,id,unit,value) == 4)
                {
                        item = new(class ware);
                        item->name = name;
                        item->id = id;
                        item->unit = unit;
                        item->o_value = value*(!undefinedp(kinds[id])?kinds[id]:100)/100;
                        item->value = item->o_value;
                        if(!undefinedp(wares[id]))
                                item->o_amount = wares[id];
                        else
                                item->o_amount = 0;
                        item->amount = item->o_amount;

                        all_wares[kind] += ({ item });
                }
                else
                {
                        kind = items[i];
                        all_wares[kind] = ({});
                }
                 this_object()->save();

        }
}

nomask void init()
{
        if(clonep())
                return;
        add_action("do_shougou",({ "shou","shougou" }));
        add_action("do_chakan",({ "chakan","list" }));
        add_action("do_paochu",({ "pao","paochu" }));
        add_action("do_check",({ "check" }));
        add_action("do_fasong","fasong");
}

nomask int do_fasong()
{
        this_player()->fasong_ware();
        return 1;
}

nomask int do_check()
{
        int i,n;
        int cha;
        int orig;
        string *kinds = keys(all_wares);

        if(!wizardp(this_player()))
                return 0;

        n = sizeof(kinds);
        for(i=0;i<n;i++)
        {
                foreach(class ware oneitem in all_wares[kinds[i]])
                {
                        orig += oneitem->o_value * oneitem->o_amount; /* silver數 */
                        cha += (oneitem->o_amount -  oneitem->amount)*oneitem->o_value;
                }
        }

        printf("此地初始總價值數為：%d 兩白銀\n當前數值差：%d 兩白銀\n當前總物價指數為：百分之 %d\n系統調整值：%d\n",
                orig, cha, price_rate,system_change );
        return 1;
}

nomask int do_chakan(string arg)
{
        string *kinds = keys(all_wares);
        int i,n;

        if(!n = sizeof(all_wares))
                return notify_fail("目前沒有可貿易的貨物。\n");

        if(stringp(arg))
        {
                n = sizeof(kinds);
                for(i=0;i<n;i++)
                        if(kinds[i] == arg)
                        {
                                output_list(sprintf("%d",(i+1)),this_player());
                                return 1;
                        }
                return notify_fail("你要查看哪類貨物的價格？\n");
        }
        else
        {
                int l,bk;
                string out;
                kinds += ({ "所有類別" });
                n = sizeof(kinds);
                for(i=0;i<n;i++)
                        if(strlen(kinds[i]) > l)
                                l = strlen(kinds[i]);
                out = "請選擇你要查看的貨物類別：\n";
                bk = to_int(50/(l+5));
                l++;
                for(i=0;i<n;i++)
                        out += sprintf("%-3d%-"+(string)l+"s  %s",(i+1),kinds[i],(i%bk==(bk-1))||i==n-1?"\n":"" );
                write(out);
                input_to((: output_list :),this_player());
                return 1;
        }
}

nomask protected void output_list(string number,object who)
{
        int i,n;
        string output,*kinds = keys(all_wares);

        if(!objectp(who) || (number[0] == 'q'))
                return;

        if(!sscanf(number,"%d",n))
        {
                write("請選擇你要查看的貨物類別：\n");
                input_to((: output_list :),who);
                return;
        }

        n--;
        if( (n < 0 ) || (n > sizeof(kinds)) )
        {
                write("請選擇你要查看的貨物類別：\n");
                input_to((: output_list :),who);
                return;
        }

        if(n < sizeof(kinds))
        {
                output = sprintf("本貨棧目前可以貿易的%s類貨物：\n",kinds[n]);
                output += sprintf("%-8s%-20s %|8s%|6s%12s/%s\n","種類","貨物名稱","數量","單位","賣出價","買入價(單位：銀子)");
                output += "-------------------------------------------------------------------------\n";
                output += list_one_kind(kinds[n]);
                write(output);
                return;
        }

        else
        {
                output = "本貨棧目前所有可以貿易的貨物：\n";
                output += sprintf("%-8s%-20s %|8s%|6s%12s/%s\n","種類","貨物名稱","數量","單位","賣出價","買入價(單位：銀子)");
                output += "-------------------------------------------------------------------------\n";
                for(i=0;i<n;i++)
                        output += list_one_kind(kinds[i]);
                who->start_more(output);
                return;
        }
}

nomask protected string list_one_kind(string kind)
{
        int i,n;
        string output = "";
        class ware *items;

        if(!stringp(kind) || undefinedp(all_wares[kind]))
                return "";

        items = all_wares[kind];

        n = sizeof(items);
        for(i=0;i<n;i++)
        {
                int sell;

                if(items[i]->amount <1)
                        output += sprintf("%-8s%-20s%|14s    %8d/%-8d\n",
                                i==0?kind:"",
                                sprintf("%s(%s)",items[i]->name,items[i]->id),
                                "[無  貨]",
                                (sell = to_int(items[i]->value*price_rate/100)),
                                sell*IN_OUT_RATE);
                else
                        output += sprintf("%-8s%-20s%8d%|6s    %8d/%-8d\n",
                                i==0?kind:"",
                                sprintf("%s(%s)",items[i]->name,items[i]->id),
                                items[i]->amount,items[i]->unit,
                                (sell = to_int(items[i]->value*price_rate/100)),
                                sell*IN_OUT_RATE);
        }
        return output;
}

nomask protected int do_shougou(string arg)
{
        class ware item;
        int n,i,num;
        string *kinds = keys(all_wares);

        if(no_trade)
                return notify_fail("現在正在盤庫，請等一下再來。\n");

/*
#ifdef IN_TEST
        if(!wizardp(this_player()))
                return notify_fail("測試期間不允許玩家參與貿易。\n");
#else
        if(wizardp(this_player()))
                return notify_fail("正式運行期間不允許巫師參與貿易。\n");
#endif
*/

        if( !stringp(arg) || (arg == "") )
                return notify_fail("你要收購什麼貨物？\n");

        if(sscanf(arg,"%d %s",num,arg) == 2)
                if(num < 1)
                        return notify_fail("收購數量至少為 1。");

        n = sizeof(kinds);
        for(i=0;i<n;i++)
        {
                foreach(class ware oneitem in all_wares[kinds[i]])
                        if(oneitem->id == arg)
                        {
                                item = oneitem;
                                break;
                        }
        }

        if(!item)
                return notify_fail("你要收購什麼貨物？\n");

        if(item->amount < 1)
                return notify_fail(sprintf("最近本地%s已經斷貨了，您過一段時間在來看看吧。\n",
                        item->name));

        if(num > 0)
        {
                get_shougou_amount(sprintf("%d",num),this_player(),item);
                return 1;
        }

        write(sprintf("您要收購多少%s%s？",item->unit,item->name));
        input_to((: get_shougou_amount :),this_player(),item);
        return 1;
}

nomask protected void get_shougou_amount(string arg,object me,class ware w)
{
        int n,value,one;
        string domain;
        //object ob;

        if(!objectp(me) || (arg[0] == 'q'))
                return;

        if(!sscanf(arg,"%d",n))
        {
                write(sprintf("您要收購多少%s%s？",w->unit,w->name));
                input_to((: get_shougou_amount :),me,w);
                return;
        }

        if(n < 1)
        {
                write("收購數量至少為 1。");
                return;
        }

        if(n > 210000000)
        {
                write("收購數量不可大于 21 億。");
                return;
        }

        if( n > w->amount )
        {
                write(sprintf("對不起，本地目前只有 %d %s%s，您過一段時間在來看看吧。\n",
                        w->amount,w->unit,w->name));
                return;
        }

        one = w->value*price_rate/100;
        if(n > (MAX_TRADE/one))
        {
                write(sprintf("對不起，本地商會規定每筆貿易額不能超過%s兩白銀。\n",
                        chinese_number(MAX_TRADE)));
                return;
        }

        value = n*one;

#ifndef IN_TEST
        //if(!pay_from_bank(me,value*100))
        if( query("balance", me)<value*100 )
        {
                write(sprintf("收購 %d %s%s 共需資金 %d 兩銀子，你的銀行存款不夠。\n",
                        n,w->unit,w->name,value));
                return;
        }

        addn("balance", -value*100, me);
#endif

        if(!me->buy_in(w->name,w->id,w->unit,n,one))
        {
                write("你的收購行為沒有成功，本錢損失殆盡，請立刻向巫師通報。\n");
                log_file("warehouse",sprintf("%s(%s) 收購%s %d %s失敗，損失本金 %d 兩白銀。%s\n",
                        me->name(),query("id", me),w->name,n,w->unit,value,ctime(time())));
                return;
        }

        domain = domain_file(base_name(this_object()));

        write(sprintf("\n你從%s商棧收購了 %d %s%s。\n商棧的賬房先生在一個大本子上記了下來。\n\n",
                to_chinese(domain),n,w->unit,w->name));

        w->amount -= n;

        do_count(w->name,value);
        save();

#ifndef IN_TEST
        log_file("warehouse",sprintf("%s(%s)在%s以單價%d兩白銀收購%s%d%s。%s\n",
                me->name(),query("id", me),to_chinese(domain),one,w->name,n,w->unit,ctime(time())));
#endif

        return;
}

nomask protected int do_paochu(string arg)
{
        class ware item;
        int n,i,num;
        string *kinds = keys(all_wares);

        if(no_trade)
                return notify_fail("現在正在盤庫，請等一下再來。\n");

/*
#ifdef IN_TEST
        if(!wizardp(this_player()))
                return notify_fail("測試期間不允許玩家參與貿易。\n");
#else
        if(wizardp(this_player()))
                return notify_fail("正式運行期間不允許巫師參與貿易。\n");
#endif
*/

        if( !stringp(arg) || (arg == "") )
                return notify_fail("你要拋出什麼貨物？\n");

        if(sscanf(arg,"%d %s",num,arg) == 2)
                if(num < 1)
                        return notify_fail("拋售數量至少為 1。");

        n = sizeof(kinds);
        for(i=0;i<n;i++)
        {
                foreach(class ware oneitem in all_wares[kinds[i]])
                        if(oneitem->id == arg)
                        {
                                item = oneitem;
                                break;
                        }
        }

        if(!item)
                return notify_fail("你要拋出什麼貨物？\n");

        if(num > 0)
        {
                get_paochu_amount(sprintf("%d",num),this_player(),item);
                return 1;
        }

        write(sprintf("您要拋出多少%s%s？",item->unit,item->name));
        input_to((: get_paochu_amount :),this_player(),item);
        return 1;
}

nomask protected void get_paochu_amount(string arg,object me,class ware w)
{
        int n,value,r,one;
        string domain;

        if(!objectp(me) || (arg[0] == 'q'))
                return;

        if(!sscanf(arg,"%d",n))
        {
                write(sprintf("您要拋出多少%s%s？",w->unit,w->name));
                input_to((: get_paochu_amount :),me,w);
                return;
        }


        if(n < 1)
        {
                write("拋售數量至少為 1。");
                return;
        }

        one = w->value*price_rate/100*IN_OUT_RATE;

        if(n > (MAX_TRADE/one))
        {
                write(sprintf("對不起，本地商會規定每筆貿易額不能超過%s兩白銀。\n",
                        chinese_number(MAX_TRADE)));
                return;
        }

        if(!(r = me->sell_out(w->id,n,one)))
        {
                write(sprintf("你在本地沒有%s。\n",w->name));
                return;
        }

        if(r == -1)
        {
                write(sprintf("你在本地沒有這麼多數量的%s。\n",w->name));
                return;
        }

        domain = domain_file(base_name(this_object()));
        value = n*one;

#ifndef IN_TEST
        /*
        if( !save_to_bank(me,value*100) )
        {
                tell_object(me,"你的貨款全部損失了，請向巫師報告。\n");
                log_file("warehouse",sprintf("%s(%s)由于銀行存款超額拋售物品時損失了 %d 兩銀子。%s\n",
                        me->name(),query("id", me),value,ctime(time())));
                return 0;
        }
        */
        addn("balance", value*100, me);
#endif

        write(sprintf("你在本地拋售了 %d %s%s，\n應得貨款 %d 兩銀子已存入您的銀行賬戶。\n",
                n,w->unit,w->name,value));

        w->amount += n;
        do_count(w->name,-value);
        save();

#ifndef IN_TEST
        log_file("warehouse",sprintf("%s(%s)在%s以單價%d兩白銀拋出%s%d%s。%s\n",
                me->name(),query("id", me),to_chinese(domain),one,w->name,n,w->unit,ctime(time())));
#endif
}

// 系統控制的隨機變動
nomask void random_change(int sum)
{

        /*
        if(!previous_object()
        || (geteuid(previous_object()) != ROOT_UID))
                return;
        */

        if(!sum)
                return;

        no_trade = 1;   // 變動期間禁止貿易

        system_change += sum;
        do_count("商品",sum*100);
        save();
        log_file("business",sprintf("%s: 商品價格隨機變動 %s 涉及總金額 %d 兩白銀. %s\n",
                domain_file(base_name(this_object())),
                sum > 0 ? "上調" : "下跌",
                sum*100, ctime(time())));
        no_trade = 0;
}

// 系統控制的恢復
nomask void random_recover()
{
        string *cs;
        string current_cs;
        int max,i,n,flag;
        class ware *items;

/*
        if(!previous_object()
        || (geteuid(previous_object()) != ROOT_UID))
                return;
*/

        no_trade = 1;   // 變動期間禁止貿易

        if(sizeof(changed_class) >= sizeof(cs = keys(all_wares)))
                changed_class = ({});

        for(i=0;i<sizeof(cs);i++)
        {
        /*
                if(member_array(cs[i],changed_class) == -1)
                { current_cs = cs[i]; break; }

        changed_class += ({ current_cs });

        items = all_wares[current_cs];
        n = sizeof(items);
        */

        max = change_max;

        // foreach(class ware oneitem in all_wares[current_cs])
        foreach(class ware oneitem in all_wares[cs[i]])
        {
                int diff,ch;

                if(max < 50)
                        break;
                if(max < oneitem->o_value)
                        continue;

                if(!diff = oneitem->o_amount - oneitem->amount)
                        continue;
                ch = to_int(max/oneitem->o_value);
                if(abs(diff) < ch)
                        ch = abs(diff);
                max -= ch * oneitem->o_value;
                if(diff < 0)
                {
                        oneitem->amount -= ch;
                        flag = 1;
                }
                else
                        oneitem->amount += ch;
                log_file("business",sprintf("%s: 恢復調整 %s %s %d %s. %s\n",
                        domain_file(base_name(this_object())),
                        oneitem->id,
                        flag?"減少":"增加",
                        ch,
                        oneitem->unit,
                        ctime(time()),
                        ));
        }
        }

        do_count();
        save();

        no_trade = 0;
}
