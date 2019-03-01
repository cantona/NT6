// cmds/std/auction.c 拍賣與競價程序
// call_out() 映射控制版 for sz        xo2(xkx)
// By Shure@mudbuilder.net 2001-8-17
/*
key  string ob_id      物品ID
v[0] object obj               拍賣物品            
v[1] int    ob_price   競標價格                      
v[2] object ob_auction 競標者                      
v[3] object ob_onwer   物品所有者              
v[4] string ob_desc    物品所有者對該物品的介紹
v[5] string auction_id 競標者ID
v[6] string onwer_id   物主ID
v[7] string ob_name    物品名稱
v[8] string ob_long    物品描述

mapping        structure:
auction[obj : {ob, ob_price, ob_auction, ob_onwer, ob_desc, auction_id,        ...} ]
*/

#include <ansi.h>
inherit        F_DBASE;

#define        PRICE_DIFFERENCE 100

mapping auction = ([]);

// 狀態變化的控制中心
void auction_chat(string msg);        
void auction_state_check(int times, int        s_times, int last_price, string        obj_id); 
// 靜止的狀態切換
void auction_end(string        ob_name, int ob_price, mixed ob_auction, object        ob_onwer, object ob, string ob_id);
void auction_cancel(string ob_id, object discredit_1, object discredit_2);
// 實現拍賣
void get_ob_desc(string        desc, object me, string        str, int num);
void choise_secret(string decide, object me, string ob_id, string desc,        int num);
// 數據反饋
int player_demand(int num, string unit,        object me, string flag);
int player_bank(object ob);
int player_pay(object who, int amount);
int help();
int help_2();

// channeld.c需要增加auction頻道
/*
        "auction":([        "msg_speak": HIY "【拍賣場】%s:        %s\n" NOR,
                        "msg_color": HIY,
                ]),
*/

int clean_up(){        return 1;}

void create()
{
        seteuid(ROOT_UID);
        set("name", "拍賣指令");
        set("id", "jiaoyi");
        set("channel_id","");
}

void auction_chat(string msg) 
{        
        msg = replace_string(msg, NOR, HIY);        
        CHANNEL_D->do_channel(this_object(),"jiaoyi",msg);
}

void auction_state_check(int times, int        s_times, int last_price, string        obj_id)
{
        int    i, ob_price, flag1 = 0, flag2 = 0;
        object ob, ob_auction, ob_onwer, new_auction, new_onwer, nul;
        mixed  *v;
        string *k, ob_name, ob_id, str;
        
        // 重新定位此物品，避免因為其他物品被清除導致索引號變化
        k = keys(auction);
        i = member_array(obj_id,k); 
        v = values(auction)[i];
        ob_id           = k[i];
        ob           = v[0];
        ob_price   = v[1];
        ob_auction = v[2];
        ob_onwer   = v[3];
        ob_name           = v[7];
        
        if(!objectp(ob_auction)        && !stringp(ob_auction))
        {
                flag1++;
                if(objectp(new_auction = find_player(v[5])))
                {
                        ob_auction = new_auction;
                        flag1 =        0;
                }
        }
        if(!objectp(ob_onwer))
        {
                flag2++;
                if(objectp(new_onwer = find_player(v[6])))
                {
                        ob_onwer = new_onwer;
                        flag2 =        0;
                }
        }

        if(flag2 && !flag1) 
        {
                str="由于賣方缺席，取消"+ob_name+"的拍賣";
                auction_chat(str);
                auction_cancel(ob_id, ob_auction, nul);
                return;
        }
        if(!objectp(ob)        || !objectp(present(ob,ob_onwer)))
        {
                str="由于賣方保管不當，拍賣物品"+ob_name+"丟失，本次拍賣取消！\n";
                auction_chat(str);
                ob_onwer->delete_temp("auctioning");
                auction_cancel(ob_id, ob_auction, nul);
                return;
        }
        if(times < 120)
        {
                times++;
                if(ob_price > last_price)
                {
                        s_times        = 0;
                        call_out("auction_state_check",        20, times, s_times, ob_price, ob_id);
                }
                else
                {
                        s_times++;
                        if(s_times<4)
                        {
                                str = HIR"第"+CHINESE_D->chinese_number(s_times)+"次喊價:"HIY"拍賣"+ob_name+"，現價"+MONEY_D->price_str(ob_price)+"!!";
                                auction_chat(str);   
                                call_out("auction_state_check",        30, times, s_times, ob_price, ob_id);
                        }
                        else
                        {
                                if(flag1 && !flag2)
                                {
                                        str="由于買方缺席，取消"+ob_name+"的拍賣！";
                                        auction_chat(str);
                                        auction_cancel(ob_id, ob_onwer,        nul);
                                        return;
                                }
                                if(flag1 && flag2)
                                {
                                        str="由于買賣雙方缺席，取消"+ob_name+"的拍賣！";
                                        auction_chat(str);
                                        auction_cancel(ob_id, nul, nul);
                                        return;
                                }        
                                auction_end(ob_name, ob_price, ob_auction, ob_onwer, ob, ob_id);
                        }
                }
        }
        else
        {
                if(flag1 && !flag2)
                {
                        str="由于買方缺席，取消"+ob_name+"的拍賣！";
                        auction_chat(str);
                        auction_cancel(ob_id, ob_onwer,        nul);
                        return;
                }
                if(flag1 && flag2)
                {
                        str="由于買賣雙方缺席，取消"+ob_name+"的拍賣！";
                        auction_chat(str);
                        auction_cancel(ob_id, nul, nul);
                        return;
                }
                str = "時間已到，拍賣"+ob_name+"的過程到此為止！\n";
                auction_chat(str);
                auction_end(ob_name, ob_price, ob_auction, ob_onwer, ob, ob_id);
                return;
        }
        return ;
}

void auction_end(string        ob_name, int ob_price, mixed ob_auction, object        ob_onwer, object ob, string ob_id)
{

        object        *inv, *en_inv, nul;
        string onwer_id, str;

        if(!objectp(ob_onwer))        return;         // 雖然不太可能發生，但還是判斷下保險
        onwer_id = ob_onwer->query_temp("auction/"+ob_id);
        
        if(stringp(ob_auction))
        {
                str=onwer_id+"以底價"+MONEY_D->price_str(ob_price)+"拍賣"+
                ob_name+"，由于無人投標，本次拍賣無效！\n";                
                auction_cancel(ob_id, ob_onwer,        nul);
                tell_object(ob_onwer,HIR"很遺憾！，"NOR"你的"+ob_name+"無人投標，本次拍賣無效！\n");
                ob_onwer->set("auction_fail",ob_onwer->query("mud_age"));
        }
        else
        {
                str=ob_auction->query("name")+"("+ob_auction->query("id")+")"+"出價"+MONEY_D->price_str(ob_price)+"競標"+
                ob_name+"成功，本次拍賣成交！\n";
                        
                // 買賣雙方金錢物品的交換，買方需交成交價10%的中介費
                if(!player_pay(ob_auction, (int)(ob_price*11/10))) 
                {
                        str="由于買方無力支付競價，取消"+ob_name+"的拍賣！\n";
                        ob_auction->delete_temp("auctioning");
                        auction_cancel(ob_id, ob_onwer,        nul);
                }
                else
                {
                        inv = all_inventory(ob_auction); 
                        en_inv = all_inventory(environment(ob_auction)); 
                        tell_object(ob_auction,"恭喜！你競標成功，得到了"+ob_name+"\n所需款額包含10%的中介費已經交付訖。\n");
                        
                        if(!ob->move(ob_auction) || (inv && sizeof(inv)        > 49))
                        {
                                if(en_inv && sizeof(en_inv) < 49)
                                {
                                        tell_object(ob_auction,        "你手頭已經拿不下了,東西落到了你的腳邊..\n");
                                        ob->move(environment(ob_auction)); 
                                }
                                else
                                {
                                        tell_object(ob_auction,        "此次拍賣所得由于你無力保管而收歸國有！\n");
                                        destruct(ob);
                                }
                        }        
                        tell_object(ob_onwer,ob_name+"拍賣成功！所得款已經自動轉至你的錢莊帳戶。\n");
                        ob_onwer->add("balance",ob_price);
                        auction_cancel(ob_id, ob_auction, ob_onwer);
                }
        }
        auction_chat(str);
        return;
}

void auction_cancel(string ob_id, object discredit_1, object discredit_2)
{
        if(member_array(ob_id, keys(auction)) != -1)
                map_delete(auction, ob_id);

        if(objectp(discredit_1))
                discredit_1->delete("discredit/"+ob_id);
        if(objectp(discredit_2))
                discredit_2->delete("discredit/"+ob_id);
}

int main(object        me,string arg)
{
        int i, j, k, coin, guaranty, num, index, cheat_times, ob_price,value, *check_v;
        mixed *ob_value, *v, *v2;
        string str, unit, *tuned_ch, *ob_key, ob_id, *check_k;
        object ob, obj;
        mapping check;
        
        ob_key = keys(auction);
        ob_value = values(auction);
        check = me->query("discredit");
        cheat_times = sizeof(check);
/*

if(!this_player()->query("canpaimai"))
{
    write("sorry, currently disable by scatter\n");
    return 1;
}
*/
        
        if(!arg)
        {
                tuned_ch = me->query("channels");
                if( !pointerp(tuned_ch)        )
                        me->set("channels", ({ "jiaoyi" }) );
                else if( member_array("jiaoyi", tuned_ch) == -1 )
                        me->set("channels", tuned_ch + ({ "jiaoyi" }) );
                tell_object(me,"\n你的交易頻道(jiaoyi)現在處于開通狀態\n");
                return 1;
        }        
                
        if(arg == "-l")
        {
                if(!sizeof(auction))
                {
                        tell_object(me,"目前沒有物品被拍賣。\n");
                        return 1;
                }
                str=HIG"當前拍賣物品清單：\n\n";
                str += sprintf(HIC"≡"HIY"────────────────────────────────"HIC"≡\n"NOR);
                str += "  物品名稱                   當前標價                 最高競價者\n";
                str += HIG" ※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※ \n"NOR;
                
                for(i=0; i<sizeof(auction);i++)
                {
                        v = ob_value[i];

                        str += sprintf("  %-25s  ", v[7]);
                        str += sprintf("%-25s  ", MONEY_D->price_str(v[1]));
                        str += sprintf("%-10s  \n", (!stringp(v[2]))? v[5] : "");
                }
                str += "\n\n";
                str += sprintf(HIC"≡"HIY"────────────────────────────────"HIC"≡\n"NOR);
                me->start_more(str);
                return 1;
        }
        if(arg == "-i")
        {
                if(!sizeof(auction))
                {
                        tell_object(me,"目前沒有物品被拍賣。\n");
                        return 1;
                }
                str=HIG"當前拍賣物品詳細介紹：\n\n"NOR;
                for(i=0; i<sizeof(auction);i++)
                {
                        v = ob_value[i];

                        str+=HIG"------------"NOR"\n物品名稱： "+v[7]+
                        "\n物品描述："+v[8]+
                        "\n物主介紹："+v[4]+
                        "\n物主："+v[6]+"\n\n";
                }
                me->start_more(str);                
                return 1;
        }
        if(arg == "-h")
                return help_2();
        if(sscanf(arg,"%s for %d %s",str,num,unit) == 3)
        {
                
                str = lower_case(str);
                if(me->query("age") < 16)
                {
                        tell_object(me,"你還沒有成年，能對自己的拍賣行為負責嗎？\n");
                        return 1;
                }                        
                if(me->query("combat_exp") < 10000)
                {
                        tell_object(me,"你雖已成年，但是涉世經驗太少，無法對自己的拍賣行為負責。\n");
                        return 1;
                }


                                if(unit != "gold" && unit !="silver")
                                {
                                        write("現在只接受以黃金(gold)和白銀（silver)交易\n");
                                        return 1;
                                }

                                if( num < 0 )
                                {
                                        write("請不要做違法事情\n");
                                        return 1;
                                }

                                if( num > 500 )
                                {
                                        write("不能超過五百兩黃金\n");
                                        return 1;
                                }



                if(cheat_times && !me->query_temp("auctioning"))
                {
                        check_v = values(check);
                        check_k = keys(check);
                        for(j = 0; j < sizeof(check_v); j++)
                        {
                                if(me->query("mud_age") - check_v[j] < 3600*cheat_times)        
                                {
                                        tell_object(me,"你由于在某次拍賣過程中信譽值降低，暫時無權參與。\n");
                                        return 1;
                                }
                                else map_delete(check, check_k[j]);                        
                        }
                }
                if(me->query("mud_age")        - me->query("auction_fail") < 60)
                {
                        tell_object(me,"你上次拍賣的物品無人問津，這回還是先花點時間調查市場吧。\n");
                        return 1;                
                }
                if(sizeof(auction) > 4) // 決定同時間內有多少拍賣進程可以並存
                {
                        tell_object(me,"拍賣物品隊列已滿，請少候。\n");
                        return 1;
                }
                if(!objectp(ob = present(str,me)))
                {
                        tell_object(me,"你身上沒有 "+HIG+str+NOR+" 這件物品。\n");
                        return 1;
                }
                ob_id = ob->query("id");                
                if(member_array(ob_id, ob_key)!= -1)
                {
                        tell_object(me,"你晚了一步，這類物品已經有人拍賣了。\n");
                        return 1;
                }
                
                if( ob->query("money_id") || ob->is_character() || ob_id == "corpse" || ob_id == "skeleton" || ob_id == "huo ba" || ob_id == "deng long" || ob_id == "la zhu"||ob->query("no_drop"))
                {
                        tell_object(me,"這件物品不能參加拍賣。\n");
                        return 1;
                }
                // 克扣拍賣手續費10%
                
                value = ob->query("value");
                if (value < 30)
                {
                        write(ob->query("name") + "一文不值！不能參加拍賣。\n");
                        return 1;
                }
                unit = lower_case(unit);
                if(!(num = player_demand(num, unit, me,        "sale"))) return 1;
                guaranty = (int)(num/50);                
                if(!player_pay(me, guaranty)) 
                {
                        tell_object(me,"你全部的身家財產尚不足以交納拍賣保証金！(如果使用銀票，請事先兌換)\n");
                        return 1;
                }                
                write("你所要拍賣的物品："+ob->query("name")+"， 底價："+MONEY_D->price_str(num)+"\n\n");
                write("請輸入你對該物品的介紹（控制在50個字符內）\n直接按回車(enter)可以忽略此項。\n");
                input_to("get_ob_desc",        me, ob_id, num);
                return 1;
        }
        if(sscanf(arg,"%s add %d %s", ob_id,num,unit) == 3)
        {
                
                if(me->query("age") < 16)
                {
                        tell_object(me,"你還沒有成年，能對自己的拍賣行為負責嗎？\n");                        
                        return 1;
                }


                                if(unit != "gold")
                                {
                                        write("現在只接受以黃金(gold)叫價\n");
                                        return 1;
                                }

                                if( num < 0 )
                                {
                                        write("請不要做違法事情\n");
                                        return 1;
                                }

                                if( num > 5 )
                                {
                                        write("現在限制一次最多家五兩黃金以避免不必要的問題產生\n");
                                        return 1;
                                }


                if(me->query("combat_exp") < 10000)
                {
                        tell_object(me,"你雖已成年，但是涉世經驗太少，無法對自己的拍賣行為負責。\n");
                        return 1;
                }
                if(cheat_times && !me->query_temp("auctioning"))
                {
                        check_v = values(check);
                        check_k = keys(check);
                        for(j = 0; j < sizeof(check_v); j++)
                        {
                                if(me->query("mud_age") - check_v[j] < 3600*cheat_times)        
                                {
                                        tell_object(me,"你由于在某次拍賣過程中信譽值降低，暫時無權參與。\n");
                                        return 1;
                                }
                                else map_delete(check, check_k[j]);                        
                        }
                }
                if((index = member_array(ob_id, ob_key)) == -1)
                {
                        for(k = 0; k < sizeof(auction); k++)
                        {
                                if (strsrch(ob_key[k], ob_id) == -1)
                                        continue;
                                index = k;
                        }
                        if (index < 0)
                        {
                                tell_object(me,"目前的拍賣序列中沒有這個物品！\n\n指令：auction <物品ID> add <差價值> <貨幣單位>\n請用auction -l指令查詢當前的物品拍賣情況。\n");
                                return 1;
                        }
                }

                v2 = ob_value[index];
                obj = v2[0];
                ob_price = v2[1];
                ob_id = ob_key[index];
                
                if(objectp(obj)        && v2[3]        == me)
                {
                        tell_object(me,"那是你自己的拍賣物品，想暗地托價不成？\n");
                        return 1;
                }
                coin = player_bank(me);
                unit = lower_case(unit);
                if(!(num = player_demand(num, unit, me,        "add"))) return        1;
                
                /*
                if((int)((num + ob_price)*11/10) > coin)
                {
                        tell_object(me,"你沒有這麼多錢可以償付這個出價（預計價含10%中介費）。\n");
                        return 1;
                }
                */
                if ( intp (me->query("paimai/bathtime")) )
                if (uptime() < me->query("paimai/bathtime") + 5 )
                        return notify_fail("你才投的標又投，想什麼壞主意呢。\n");

                if((int)((num + ob_price)*11/10 > this_player()->query("balance")))
                                {
                                                tell_object(me,"錢莊裡沒有足夠的存款來競拍賣該物品。（預計價含10%中介費）。\n");
                                                return 1;
                                }


                me->set("discredit/"+ob_id,me->query("mud_age"));
                me->set_temp("auctioning",1);
                v2[1] = num + ob_price;
                v2[2] = me;
                v2[5] = me->query("id");
                str = me->query("name")+"("+me->query("id")+")投標"+v2[7]+"，競價："+MONEY_D->price_str(v2[1])+"!\n";
                auction_chat(str);
                me->set("paimai/bathtime",uptime() );
                return 1;
        }
        else return help();
}

void get_ob_desc(string        desc, object me, string        str, int num)
{
        write("\n");
        if (strlen(desc) > 60)
        {
                write("您對物品的介紹太長了，請注意言簡意賅。\n");
                input_to("get_ob_desc",        me, str, num);
                return ;
        }
        write("作為物主，您是否願意在拍賣過程中透露自己姓名？(y/n)\n");
        input_to("choise_secret", me, str, desc, num);        
        return;
}

void choise_secret(string yn, object me, string        ob_id, string desc, int        num)
{
        mixed *values;
        string ob_name,        onwer_id, str;
        object ob;

        if (yn[0] != 'y' && yn[0] != 'Y')
                me->set_temp("auction/"+ob_id, "某人");
        else 
                me->set_temp("auction/"+ob_id, me->query("name")+"("+me->query("id")+")");
        if(!objectp(ob = present(ob_id,        me)))
        {
                tell_object(me,"你身上已經沒有這件東西了，不能參加拍賣。\n");
                return;
        }                
        if(sizeof(auction) && member_array(ob_id,keys(auction))!= -1)
        {
                tell_object(me,"你晚了一步，這類物品已經被人搶先拍賣了。\n");
                return;
        }
        onwer_id = me->query_temp("auction/"+ob_id);
        ob_name        = ob->query("name")+"("+ob_id+")";

        // 以下設置信任屬性，判斷違反拍賣規則的玩家
        me->set("discredit/"+ob_id, me->query("mud_age"));
        me->set_temp("auctioning", 1);
        
        values = ({ob, num, "",        me , desc, "", onwer_id, ob_name, ob->long()});
        auction[ob_id] = values;
        str = me->name()+"("+me->query("id")+")啟動拍賣進程。";
        CHANNEL_D->do_channel(this_object(),"sys",str);
        str = onwer_id+"現在開始拍賣"+ob_name+"，底價："+MONEY_D->price_str(num)+"。\n";
        auction_chat(str);
        call_out("auction_state_check",        30, 0, 0, num,ob_id);
        return;
}

int player_demand(int num, string unit,        object me, string flag)
{
        switch(unit)
        {
                case "coin":break;
                case "silver":num*=100;break;
                case "gold":num*=10000;break;
                case "cash":
                case "thousand-cash":
                        tell_object(me,"拍賣交易中不得使用銀票，請先在錢莊兌換成硬通貨。\n");
                        return 0;
                default:
                        tell_object(me,"非法的貨幣單位！\nvalid        unit: coin, silver, gold\n");
                        return 0;
        }
        if (num        < 1000 && flag == "add")
        {
                tell_object(me,"拍賣規則：差價以十兩白銀為底線。\n");
                return 0;
        }
        if (num        < 1000 && flag == "sale")
        {
                tell_object(me,"對不起，本行不支持無底價拍賣，10兩白銀是出價底線。\n");
                return 0;
        }
        return num;
}

int player_bank(object ob)
{
        object g_ob;
        object c_ob;
        object s_ob;
        int total;

        total =        ob->query("balance");

        g_ob = present("gold_money", ob);
        c_ob = present("coin_money", ob);
        s_ob = present("silver_money", ob);

        if (g_ob) total        += g_ob->query_amount()        * 10000;
        if (s_ob) total        += s_ob->query_amount()        * 100;
        if (c_ob)   total += c_ob->query_amount();
        return total;
}

int player_pay(object who, int amount)
{
        object g_ob, s_ob, c_ob;
        int gc,        sc, cc,        left, total;

        seteuid(getuid());

        if (g_ob = present("gold_money", who))
                gc = g_ob->query_amount();
        else
                gc = 0;
        if (s_ob = present("silver_money", who))
                sc = s_ob->query_amount();
        else
                sc = 0;
        if (c_ob = present("coin_money", who))
                cc = c_ob->query_amount();
        else
                cc = 0;
        total =        cc + sc        * 100 +        gc * 10000;
        
        if ( total < amount )
        {
                if((amount-total) > who->query("balance"))
                        return 0;
                if(objectp(c_ob)) destruct(c_ob);
                if(objectp(s_ob)) destruct(s_ob);
                if(objectp(g_ob)) destruct(g_ob);                
                who->add("balance",-(amount-total)); 
                        tell_object(who,"你身上的零錢不夠，所需費用已直接從錢莊帳戶上扣除。\n\n");
                return 1;
        }
        else 
        {
                left = total - amount;
                gc = left / 10000;
                left = left % 10000;
                sc = left / 100;
                cc = left % 100;

                if (g_ob)
                        g_ob->set_amount(gc);
                else sc        += (gc * 100);
                if (s_ob)
                        s_ob->set_amount(sc);
                else if        (sc) {
                        s_ob = new(SILVER_OB);
                        s_ob->set_amount(sc);
                        s_ob->move(who);
                }
                if (c_ob)
                        c_ob->set_amount(cc);
                else if        (cc) {
                        c_ob = new(COIN_OB);
                        c_ob->set_amount(cc);
                        c_ob->move(who);
                }
                return 1;
        }
}

int help()
{
    write(@HELP命令格式：
 
    查看目前處于競拍狀態的物品清單：paimai -l
    查看目前處于競拍狀態的物品介紹：paimai -i    
    拍賣物品：paimai <物品ID> for <底價值> <貨幣單位>
    競拍物品：paimai <物品ID> add <加價值> <貨幣單位> 
    
    查看詳細的拍賣規則：paimai -h
    
HELP
    );
    return 1;
}

int help_2()
{    
    write(@HELP拍賣規則說明文檔：  

    1. 玩家在18歲以後，自身經驗值達到1000點即有權利參與拍賣。  
    
    2. 拍賣過程中銀票無效，請先去錢莊兌換成硬通貨，如黃金、白銀、銅錢。
    
    3. 當有人拍賣物品時，拍賣進程正式開始（拍賣底價不得少于10兩白銀），此時玩家可以
       以至少1兩白銀（或100文銅錢）的最低差價值參加競拍，如果一段時間內無人投標，將
       進行喊價，三次喊價後仍然無人出價，則拍賣終止。倘若一直有人投標，到了規定時間，
       此次拍賣活動仍會被終止。拍賣場最大允許5件物品同時拍賣。
       
    4. 拍賣活動終止後，最後出價者為勝，貨款從買者手邊及錢莊提取，物品直接轉移到買者
       身上，如果不堪負重則放在買者所在房間之中，如果房間也無法裝下，物品作沒收處理，
       切記！物主所得款額直接轉至其錢莊帳戶。拍賣開始時對賣方收取底價2%的手續費。倘
       若拍賣過程中始終無人投標，拍賣過程宣布失敗，手續費恕不退還物主。拍賣成功，買
       方需按成交價交納10%的中介費。
       
    5. 拍賣過程中，以下行為當作違反拍賣規則處理：買賣雙方的任何一人離開遊戲導致拍賣
       進程中斷；物品離開了物主本人；拍賣結束時買方無力償付成交價。發生上述情況之一，
       責任方信譽度會降低，懲罰是一小時內不得參加任何與拍賣有關的活動。如果在禁止拍
       賣的時間內再次違規，則禁止時間隨違規次數累加。倘若拍賣物品三次喊價之後因為無
       人競標而取消，賣家在一分鐘內不得再拍賣其他物品。
    
       Shure
       2001.8.
HELP
    );
    return 1;
}  
