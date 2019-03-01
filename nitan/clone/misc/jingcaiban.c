// jingcaiban.c

#include <ansi.h>
inherit ITEM;
inherit F_SAVE;

// 全局變量，即儲存玩家押注的所有數據
mapping *all_biao;
// 全局變量，此處為目前數量
int num;
// 全局變量，此處為最終結杲
int jieguo;

// 以下四行為函數聲明
int do_read(string);
int do_post(string);
int do_ya(string);
void enough_rest();

void create()
{
        set_name(HIY"世界杯亞洲Ｂ組十強賽競猜版"NOR, ({ "board", "ban"}) );
        set("long", "這是一個記錄玩家的競猜押注情況的版。
押注請read rules，查看目前的投注情況請read ban。\n");
        set("unit", "張");
        set("no_put", 1);
        set("no_get", 1);
//設大點不讓玩家Get
        set_weight(900000000);
        seteuid(getuid());
        restore();
}

void init()
{
        add_action("do_read", "read");
        add_action("do_post", "post");
        add_action("do_ya","ya");
        add_action("do_duijiang","duijiang");
        add_action("do_duijiang","duixian");
}

string query_save_file()
{
// 定義一個儲存文件的路徑
        return DATA_DIR + "board/jingcai_b";
}

// 玩家下注
int do_ya(string arg)
{
        int i,j;
        object me,ob;
        mapping biao;
        
        me = this_player();
// 表示停止下注，由巫師在do_post()函數裡加入
        if(query("end_ya"))
                return notify_fail("截止時間已過，下回趕早。\n");
// 防止多人同意押注產生意外
        if (query_temp("busy"))
                return notify_fail("稍候........\n");
// 調玩家身上的參數
        if( query("jingcai", me) )
                return notify_fail("每人只能押一次！\n");
// 分析玩家指令
        if(!arg || sscanf(arg, "%d %d", i, j) != 2)
                return notify_fail("命令格式：ya <分數> <多少兩黃金>\n");
// 排除一些不可能的押注可能
        if(i<10 || i>22)
                return notify_fail("不可能吧？你是不是想白送錢？\n");
// 至少1gold
        if(j < 1)
                return notify_fail("你想白賺啊？\n");
// 上限，可以自由調整
        if(j > 1000)
            return notify_fail("押得太多，請少于1000。\n");
        if( j>query("balance", me)/10000 )
// 錢莊的存款不夠押的錢
                return notify_fail("這裡不收現金！到錢莊存夠了錢再來！”\n");
        message_vision("$N想了半天大聲喊道：“我認為中國隊能拿到 "+i+" 分！押 "+j+" 兩黃金！”\n",me);
        addn("balance", -j*10000, me);
        tell_object(me,"錢莊已經扣除了你押下的"+j+"兩黃金。請等候結果吧！\n");
// 在玩家身上設下押的結果
        set("jingcai/win", i, me);
// 押的黃金數
        set("jingcai/gold", j, me);
// 這是一個記錄該玩家押注數據的映射
        biao = ([
                "id":query("id", me),
                "name":query("name", me),
                "win":i,
                "gold":j,
        ]);
        if( !pointerp(all_biao) ) all_biao = ({ biao });
        else all_biao += ({ biao });
//儲存進這個文件對應的.o文件裡
        save();
        remove_call_out("enough_rest");
//1秒後取消busy
        call_out("enough_rest", 1);
        return 1;
}

// 巫師專用，更新情況
int do_post(string arg)
{
        int i;
        object me= this_player();

        if(!wizardp(me)) return 0;
        if( !arg) return notify_fail("你要更新什麼？\n");
// 只加數字表示更新即時情況
        if(sscanf(arg, "%d", i)==1 )
        {
// num是全程變量
                if( i > num )
                {
                        message("channel:sys", HIM"【謠言】"HIR"某人：聽說競猜版中國隊當前得分由 "+num+" 更新為 "+i+" 分！\n"NOR, users());
// 更新
                        num = i;
                        save();
                        return 1;
                }
                else return notify_fail("中國隊得分會越掙越少嗎？\n");
        }
// 加-last參數，表示更新最終結果
        if(sscanf(arg, "-last %d", i)==1 )
        {
                if( i >= num )
                {
                        message("channel:sys", HIM"【謠言】"HIR"某人：聽說競猜版最終結果公布，是 "+jieguo+" 分！押對的快去兌獎啊！\n"NOR, users());
// 更新
                        jieguo = i;
                        save();
                        return 1;
                }
                else return notify_fail("中國隊得分會越掙越少嗎？\n");
        }
        if(arg=="end")
        {
// 停止押注
                set("end_ya",1);
                message("channel:sys", HIM"【謠言】"HIR"某人：競猜版開始停止下注，請關注比賽結果！\n"NOR, users());
                save();
                return 1;
        }
        return notify_fail("你要的中國隊得分是多少？\n");
}
// 玩家查看
int do_read(string arg)
{
        int i,j,k;
        object me;
        string name,str,str1,str2;
        mapping biao;
        
        me = this_player();
        if(arg == "rules")
        {
//這個規則根據每次巫師設計的定
                write("
    世界杯外圍賽亞洲十強賽Ｂ組，中國隊能拿幾分？歡迎在此押注：
押注者以黃金為單位，最高可押一千黃金，最少也要押一兩黃金。現金
不收，必須先存進錢莊。押賭後錢莊直接扣錢。押賭時間到十月十二日
截止。押小于十三分的數字一賠十二，押十三至二十之間的數字是一賠
六，二十以上的數字是一賠十五，比賽結束，押中者按倍數返還黃金，
不中者則罷。想好了後就 "HIY"ya <分數> <多少兩黃金> "NOR"。
    當然每個ID只能押一次，押過不許後悔！\n\n");
                write("開獎後請使用duixian指令，你的獎金將自動進入你帳戶。\n");
                return 1;
        }
        if(arg == "ban")
        {
//有了分數的參數
                if(num) write( "★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n"HIG"本屆十強賽，中國已獲 "HIY+num+HIG" 分！");
                write(!jieguo ? RED"還在投注中！" : HIR"開始兌獎(duijiang)了！");
//表示還沒有數據
                if( !pointerp(all_biao) || !sizeof(all_biao) )
                {
                        write(NOR"\n還沒有人開始投注。\n");
                        return 1;
                }
                write(NOR"\n已有 "+sizeof(all_biao)+" 個玩家投注：\n"
                HIY"玩家名　　　　預測分數  　押黃金數"HIG"｜"HIY"玩家名　　　　預測分數數　押黃金數\n"
                HIG"─────────────────┼─────────────────\n");
                str1 = HIM"已經兌過獎的玩家：                "HIG"｜\n"NOR;
                str2 = HIM"還未兌過獎的玩家：                "HIG"｜\n"HIC;
                j = 0;
                k = 0;
// all_biao也是全局變量，看文件頭
                for(i=0; i<sizeof(all_biao); i++)
                {
// 取出每個押注玩家的名字
                        name = all_biao[i]["name"]+"("+all_biao[i]["id"]+")";
// dui這個參數是在兌獎後加入的，這表示沒兌獎的，加入str2
                        if(!(int)all_biao[i]["dui"])
                        {
                                str2 += sprintf("%-18s    %-5d  %-5d%s",name,(int)all_biao[i]["win"],(int)all_biao[i]["gold"],j%2?"\n":HIG"｜"HIC,);
// j和下面的k都是為了兩個一行，分行用的j%2就是除2剩下的余數，為0就換行
                                j++;
                        }
// 有dui參數的，記入str1
                        else
                        {
                                str1 += sprintf("%-18s    %-5d  %-5d%s",name,(int)all_biao[i]["win"],(int)all_biao[i]["gold"],k%2?"\n":HIG"｜"HIC,);
                                k++;
                        }
                }
/* 這裡的str1與str2可以根據不同的情況表現不同的信息，比如在比賽中，可
以根據all_biao[i]["win"]是否大于num，即目前的分數數，判斷哪些玩家還有
希望，哪些玩家已經被淘汰：str1="無獲獎希望的玩家"：......  */
//顯示信息
                write(str1+"\n"+str2+"\n"NOR);
                return 1;
        }
        else
                write("你要看什麼？押注規則請read rules，押注情況請read ban。\n");
        return 1;
}

void enough_rest()
{
        delete_temp("busy");
}
// 兌獎指令
int do_duijiang()
{
        int i,j;
        object ob, me = this_player();
        mapping biao, jingcai;

// 沒有jieguo就表示沒有開始兌獎
        if(!jieguo) return notify_fail("還未到兌獎時間！\n");
// 查找身上參數
        if( !jingcai=query("jingcai", me) )
                return notify_fail("你沒有獎的，或者已經兌過獎了！\n");
        if(query_temp("busy")) return notify_fail("稍候........\n");
        set_temp("busy",1);
// 與結果相符，即中獎
        if(jingcai["win"]==jieguo)
        {
// 1賠15
                if(jingcai["win"]>22) i = jingcai["gold"]*15;
// 1賠6
                else if(jingcai["win"]>14) i = jingcai["gold"]*6;
// 1賠12
                else i = jingcai["gold"]*12;
// 這些都可以按照設定的規則來定
                write("你押 "+jingcai["win"]+" 分 "+jingcai["gold"]+" 兩黃金，按規定得獎金 "+i+" 兩黃金，已劃入你的錢莊帳戶！\n");
                message("channel:sys", HIM"【謠言】"HIR"某人："+me->name()+"兌獎得到 "+chinese_number(i)+" 兩黃金！\n"NOR, users());
                addn("balance", i*10000, me);
        }
// 沒有對的也來個空門獎吧
        else
        {
                ob = new("/clone/food/jitui");
                ob->move(me);
                write("你沒押對，但發一個安慰獎，送你一根雞腿吧！\n");
                message_vision( HIY"競猜表上頭突然金光一閃，“撲”地掉下一根油光光的雞腿，正好掉進$N的手中。\n"NOR,me);
        }
        for(j=0; j<sizeof(all_biao); j++)
        {
// 表示此人兌過獎了
                if( all_biao[j]["id"] == query("id", me) )
                        all_biao[j]["dui"] = 1;
        }
// 存盤
        save();
// 身上參數取消，以防重復兌獎
        delete("jingcai", me);
        remove_call_out("enough_rest");
        call_out("enough_rest", 1);
        return 1;
}