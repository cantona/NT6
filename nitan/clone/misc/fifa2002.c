// jingcaiban.c

#include <ansi.h>
inherit ITEM;
inherit F_SAVE;

// 全局變量，即儲存玩家押注的所有數據
mapping *all_biao;
// 全局變量，此處為目前數量
int num;
// 全局變量，此處為最終結杲
mapping *end_biao;
int jieguo;

// 以下七行為函數聲明
int do_read(string);
int do_post(string);
int do_ya(string);
void enough_rest();
string codetoteam(string arg);
string ordercode(string arg, int arg1);
string upcase(string arg);

string *team = ({
"阿根廷","巴西","比利時","喀麥隆","中國","哥斯達黎加", "德國","丹麥",
"厄瓜多爾","西班牙","法國","克羅地亞","愛爾蘭","意大利","日本","韓國",
"墨西哥","尼日利亞","波蘭","葡萄牙","巴拉圭","俄羅斯","沙特","瑞典",
"斯洛文尼亞","塞內加爾","突尼斯","土耳其","英格蘭","美國","烏拉圭","南非"});
string *code=({
        "AR", "BR", "BE", "CM", "CN", "CR", "DE", "DK",
        "EC", "ES", "FR", "HR", "IE", "IT", "JP", "KP",
        "MX", "NG", "PL", "PT", "PY", "RU", "SA", "SE",
        "SI", "SN", "TN", "TU", "UK", "US", "UY", "ZA"
});

void create()
{
        set_name(HIY"世界盃競猜版"NOR, ({ "board", "ban"}) );
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
        return DATA_DIR + "board/fifa2002_b";
}

// 玩家下注
int do_ya(string arg)
{
        int i;
        string c, t, c1, c2, c3, c4, c5, c6, c7, c8;
        object ob, me = this_player();
        mapping biao;
        
// 表示停止下注，由巫師在do_post()函數里加入
        if(query("end_ya"))
                return notify_fail("截止時間已過，下回趕早。\n");
// 防止多人同意押注產生意外
        if (query_temp("busy"))
                return notify_fail("稍候........\n");
// 分析玩家指令
        if(!arg)
                return notify_fail("命令格式：ya <類別> <球隊> <多少兩黃金>\n");
        arg=upcase(arg);
        if(sscanf(arg, "%s %s %d", t, c, i) != 3)
                return notify_fail("命令格式：ya <類別> <球隊> <多少兩黃金>\n");
// 排除一些不可能的押注可能
        if(t != "1" && t != "2" && t != "4" && t != "8")
                return notify_fail("你總要先選定投注類別罷？\n");
// 至少1gold
        if(i < 1)
                return notify_fail("你想白賺啊？\n");
// 上限，可以自由調整
        if(i > 1000)
            return notify_fail("押得太多，請少於1000。\n");
        if( i>query("balance", me)/10000 )
// 錢莊的存款不夠押的錢
                return notify_fail("這裏不收現金！到錢莊存夠了錢再來！\n");

// 押冠軍
        switch ( t )
        {
                case "1":
// 調玩家身上的參數
                        if( query("fifa2002/1", me) )
                                return notify_fail("你只能給冠軍下一次注！\n");
                        if(codetoteam(c) == "未知國名")
                                return notify_fail("先看好國家代碼再來！\n");
                        message_vision("$N想了半天大聲喊道：“我認為"HIR+codetoteam(c)+NOR"隊能拿到冠軍！押 "HIY+chinese_number(i)+NOR" 兩黃金！”\n",me);
// 在玩家身上設下押的結果
                        set("fifa2002/1", c, me);
// 押的黃金數
                        set("fifa2002/10", i, me);
// 這是一個記錄該玩家押注數據的映射
                        biao = ([
                                "id":query("id", me),
                                "name":query("name", me),
                                "type" : 1,
                                "code" : c,
                                "gold" : i,
                        ]);
                        break;
                case "2":
// 調玩家身上的參數
                        if( query("fifa2002/2", me) )
                                return notify_fail("你只能給亞軍下一次注！\n");
                        if(codetoteam(c) == "未知國名")
                                return notify_fail("先看好國家代碼再來！\n");
                        message_vision("$N想了半天大聲喊道：“我認為"HIR+codetoteam(c)+NOR"隊能拿到亞軍！押 "HIY+chinese_number(i)+NOR" 兩黃金！”\n",me);
// 在玩家身上設下押的結果
                        set("fifa2002/2", c, me);
// 押的黃金數
                        set("fifa2002/20", i, me);
// 這是一個記錄該玩家押注數據的映射
                        biao = ([
                                "id":query("id", me),
                                "name":query("name", me),
                                "type" : 2,
                                "code" : c,
                                "gold" : i,
                        ]);
                        break;
                case "4":
// 調玩家身上的參數
                        if( query("fifa2002/4", me) )
                                return notify_fail("你只能給四強下一次注！\n");
                        if(sscanf(c, "%s-%s-%s-%s", c1, c2, c3, c4) != 4)
                                return notify_fail("國家代碼輸入格式錯！\n");
                        if(codetoteam(c1) == "未知國名")
                                return notify_fail("沒有"HIR+c1+NOR"這國家代碼！\n");
                        if(codetoteam(c2) == "未知國名")
                                return notify_fail("沒有"HIR+c2+NOR"這國家代碼！\n");
                        if(codetoteam(c3) == "未知國名")
                                return notify_fail("沒有"HIR+c3+NOR"這國家代碼！\n");
                        if(codetoteam(c4) == "未知國名")
                                return notify_fail("沒有"HIR+c4+NOR"這國家代碼！\n");
                        c=ordercode(c, 4);
                        message_vision("$N想了半天大聲喊道：“我認為"HIR+codetoteam(c1)+"、"+codetoteam(c2)+"、"+codetoteam(c3)+"、"+codetoteam(c4)+NOR"隊能進入四強！押 "HIY+chinese_number(i)+NOR" 兩黃金！”\n",me);
// 在玩家身上設下押的結果
                        set("fifa2002/4", c, me);
// 押的黃金數
                        set("fifa2002/40", i, me);
// 這是一個記錄該玩家押注數據的映射
                        biao = ([
                                "id":query("id", me),
                                "name":query("name", me),
                                "type" : 4,
                                "code" : c,
                                "gold" : i,
                        ]);
                        break;
                case "8":
// 調玩家身上的參數
                        if( query("fifa2002/8", me) )
                                return notify_fail("你只能給八強下一次注！\n");
                        if(sscanf(c, "%s-%s-%s-%s-%s-%s-%s-%s", c1, c2, c3, c4, c5, c6, c7, c8) != 8)
                                return notify_fail("國家代碼格式輸入錯！\n");
                        if(codetoteam(c1) == "未知國名")
                                return notify_fail("沒有"HIR+c1+NOR"這國家代碼！\n");
                        if(codetoteam(c2) == "未知國名")
                                return notify_fail("沒有"HIR+c2+NOR"這國家代碼！\n");
                        if(codetoteam(c3) == "未知國名")
                                return notify_fail("沒有"HIR+c3+NOR"這國家代碼！\n");
                        if(codetoteam(c4) == "未知國名")
                                return notify_fail("沒有"HIR+c4+NOR"這國家代碼！\n");
                        if(codetoteam(c5) == "未知國名")
                                return notify_fail("沒有"HIR+c5+NOR"這國家代碼！\n");
                        if(codetoteam(c6) == "未知國名")
                                return notify_fail("沒有"HIR+c6+NOR"這國家代碼！\n");
                        if(codetoteam(c7) == "未知國名")
                                return notify_fail("沒有"HIR+c7+NOR"這國家代碼！\n");
                        if(codetoteam(c8) == "未知國名")
                                return notify_fail("沒有"HIR+c8+NOR"這國家代碼！\n");
                        c=ordercode(c, 8);
                        message_vision("$N想了半天大聲喊道：“我認為"HIR+codetoteam(c1)+"、"+codetoteam(c2)+"、"+codetoteam(c3)+"、"+codetoteam(c4)+"、"+codetoteam(c5)+"、"+codetoteam(c6)+"、"+codetoteam(c7)+"、"+codetoteam(c8)+NOR"隊能進入八強！押 "HIY+chinese_number(i)+NOR" 兩黃金！”\n",me);
// 在玩家身上設下押的結果
                        set("fifa2002/8", c, me);
// 押的黃金數
                        set("fifa2002/80", i, me);
// 這是一個記錄該玩家押注數據的映射
                        biao = ([
                                "id":query("id", me),
                                "name":query("name", me),
                                "type" : 8,
                                "code" : c,
                                "gold" : i,
                        ]);
                        break;
        }
        addn("balance", -i*10000, me);
        tell_object(me,"錢莊已經扣除了你押下的"+chinese_number(i)+"兩黃金。請等候結果吧！\n");
        if( !pointerp(all_biao) ) all_biao = ({ biao });
        else all_biao += ({ biao });
// 儲存進這個文件對應的.o文件裏
        save();
        remove_call_out("enough_rest");
// 1秒後取消busy
        call_out("enough_rest", 1);
        return 1;
}

// 巫師專用，確定結果
int do_post(string arg)
{
        int i;
        string c, c1, c2, c3, c4, c5, c6, c7, c8;
        mapping end;
        object me = this_player();

        if(!wizardp(me)) return 0;
        if(arg=="end")
        {
// 停止押注
                set("end_ya", 1);
                message("channel:sys", HIM"【謠言】"HIR"某人：競猜版開始停止下注，請關注比賽結果！\n"NOR, users());
                save();
                return 1;
        }
// 分析巫師指令
        if(!arg) return notify_fail("命令格式：post <類別> <結果>\n");
        arg=upcase(arg);
        if(sscanf(arg, "%d %s", i, c) != 2 )
                return notify_fail("命令格式：post <類別> <結果>\n");
        switch ( i )
        {
                case 1:
                        message("channel:sys", HIM"【謠言】"HIR"某人：競猜版冠軍結果公佈，是 "HIY+codetoteam(c)+HIR" ！押對的快去兑獎啊！\n"NOR, users());
                        break;
                case 2:
                        message("channel:sys", HIM"【謠言】"HIR"某人：競猜版亞軍結果公佈，是 "HIY+codetoteam(c)+HIR" ！押對的快去兑獎啊！\n"NOR, users());
                        break;
                case 4:
                        c=ordercode(c, 4);
                        if(sscanf(c, "%s-%s-%s-%s", c1, c2, c3, c4) != 4)
                                return notify_fail("國家代碼輸入格式錯！\n");
                        if(codetoteam(c1) == "未知國名")
                                return notify_fail("沒有"HIR+c1+NOR"這國家代碼！\n");
                        if(codetoteam(c2) == "未知國名")
                                return notify_fail("沒有"HIR+c2+NOR"這國家代碼！\n");
                        if(codetoteam(c3) == "未知國名")
                                return notify_fail("沒有"HIR+c3+NOR"這國家代碼！\n");
                        if(codetoteam(c4) == "未知國名")
                                return notify_fail("沒有"HIR+c4+NOR"這國家代碼！\n");
                        message("channel:sys", HIM"【謠言】"HIR"某人：競猜版四強結果公佈，是 "HIY+codetoteam(c1)+"、"+codetoteam(c2)+"、"+codetoteam(c3)+"、"+codetoteam(c4)+HIR" ！押對的快去兑獎啊！\n"NOR, users());
                        break;
                case 8: 
                        c=ordercode(c, 8);
                        if(sscanf(c, "%s-%s-%s-%s-%s-%s-%s-%s", c1, c2, c3, c4, c5, c6, c7, c8) != 8)
                                return notify_fail("國家代碼格式輸入錯！\n");
                        if(codetoteam(c1) == "未知國名")
                                return notify_fail("沒有"HIR+c1+NOR"這國家代碼！\n");
                        if(codetoteam(c2) == "未知國名")
                                return notify_fail("沒有"HIR+c2+NOR"這國家代碼！\n");
                        if(codetoteam(c3) == "未知國名")
                                return notify_fail("沒有"HIR+c3+NOR"這國家代碼！\n");
                        if(codetoteam(c4) == "未知國名")
                                return notify_fail("沒有"HIR+c4+NOR"這國家代碼！\n");
                        if(codetoteam(c5) == "未知國名")
                                return notify_fail("沒有"HIR+c5+NOR"這國家代碼！\n");
                        if(codetoteam(c6) == "未知國名")
                                return notify_fail("沒有"HIR+c6+NOR"這國家代碼！\n");
                        if(codetoteam(c7) == "未知國名")
                                return notify_fail("沒有"HIR+c7+NOR"這國家代碼！\n");
                        if(codetoteam(c8) == "未知國名")
                                return notify_fail("沒有"HIR+c8+NOR"這國家代碼！\n");
                        message("channel:sys", HIM"【謠言】"HIR"某人：競猜版八強結果公佈，是 "HIY+codetoteam(c1)+"、"+codetoteam(c2)+"、"+codetoteam(c3)+"、"+codetoteam(c4)+"、"+codetoteam(c5)+"、"+codetoteam(c6)+"、"+codetoteam(c7)+"、"+codetoteam(c8)+HIR" ！押對的快去兑獎啊！\n"NOR, users());
                        break;
                default : return notify_fail(HIR"哪有這個類別！\n"NOR);
        }
// 這是一個記錄結果數據的映射
        end = ([
                "type" : i,
                "code" : c,
        ]);
// 最終結果儲存進這個文件對應的.o文件裏
        if( !pointerp(end_biao) ) end_biao = ({ end });
        else end_biao += ({ end });
        jieguo = 1;
        save();
// 更新
        return 1;
}
// 玩家查看
int do_read(string arg)
{
        int i, j;
        object me = this_player();
        string name, str, str1, str2;
        mapping biao;
        
        if(arg == "rules")
        {
//這個規則根據每次巫師設計的定
                write("
    世界盃的冠軍、亞軍、四強、八強分別誰屬？歡迎在此押注：
押注者以黃金為單位，最高可押一千黃金，最少也要押一兩黃金。現金
不收，必須先存進錢莊。押賭後錢莊直接扣錢。押賭時間到六月十日截
止。押對八強的一賠二十，四強的一賠十，冠亞軍的一賠八，比賽揭曉，
押中者按倍數返還黃金，不中者則罷。
    想好了後就 "HIR"ya <類別> <國名編號> <多少兩黃金> "NOR"。
    例如：
    想壓一千黃金給阿根廷為冠軍，則ya 1 AR 1000。
    如果認為四強是阿根廷、法國、巴西、德國，而且想押五百黃金的
話，則ya 4 AR-BR-DE-FR 500。當然，順序是無所謂的。
    當然每個ID只能押一次，押過不許後悔！\n

類    別：   "HIY"1-冠軍 2-亞軍 4-四強 8-八強"NOR"
國家編號："HIC"
           A組 法國FR    丹麥DK    烏拉圭UY    塞內加爾SN
           B組 南非ZA    西班牙ES  巴拉圭PY    斯洛文尼亞SI
           C組 巴西BR    中國CN    土耳其TU    哥斯達黎加CR
           D組 波蘭PL    美國US    韓國KP      葡萄牙PT  
           E組 德國DE    沙特SA    愛爾蘭IE    喀麥隆CM
           F組 瑞典SE    阿根廷AR  英格蘭UK    尼日利亞NG
           G組 意大利IT  墨西哥MX  克羅地亞HR  厄瓜多爾EC
           H組 日本JP    俄羅斯RU  比利時BE    突尼斯TN
\n"NOR);
                write("開獎後請使用duixian <類別> 指令，你的獎金將自動進入你帳户。\n");
                return 1;
        }
        if(arg == "ban")
        {
//有了分數的參數
                if(num) write( "★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n"HIG"世界盃賽投注競猜版  ");
                write(!jieguo ? RED"還在投注中！":HIR"開始兑獎(duijiang)了！");
//表示還沒有數據
                if( !pointerp(end_biao) || !sizeof(end_biao) )
                        write(HIY"\n巫師尚未設定結果。\n"NOR);
                else
                {
                        write(HIY"\n比賽結果\n"NOR);
                        for(i=0; i<sizeof(end_biao); i++)
                        {
                                switch ( (int)end_biao[i]["type"])
                                {
                                        case 1 : write(HIR"\n冠軍 "); break;
                                        case 2 : write(HIR"\n亞軍 "); break;
                                        case 4 : write(HIR"\n四強 "); break;
                                        case 8 : write(HIR"\n八強 "); break;
                                }
                                for (j=0; j<sizeof(code); j++)
                                        if (strsrch(end_biao[i]["code"], code[j]) >= 0)
                                                write(HIY+team[j]+" "NOR);
                        }
                }
//表示還沒有數據
                if( !pointerp(all_biao) || !sizeof(all_biao) )
                {
                        write(HIG"\n\n還沒有人開始投注。\n");
                        return 1;
                }
                write(HIG"\n\n已有 "+sizeof(all_biao)+" 個玩家投注：\n"
                HIY"玩家名         投注類別 押黃金數  　             國家名\n"
                HIG"———————————————————————————————————\n"NOR);
                str1 = HIM"已經兑過獎的玩家：                \n"NOR;
                str2 = HIM"還未兑過獎的玩家：                \n"NOR;
// all_biao也是全局變量，看文件頭
                for(i=0; i<sizeof(all_biao); i++)
                {
// 取出每個押注玩家的名字
                        str = sprintf("%18s ", all_biao[i]["name"]+"("+all_biao[i]["id"]+")");
                        switch ( (int)all_biao[i]["type"])
                        {
                                case 1 : str += HIR"冠軍"NOR; break;
                                case 2 : str += HIR"亞軍"NOR; break;
                                case 4 : str += HIR"四強"NOR; break;
                                case 8 : str += HIR"八強"NOR; break;
                        }
                        str += sprintf("%8s", all_biao[i]["gold"]+"兩 ");
                        for (j=0; j<sizeof(code); j++)
                                if (strsrch(all_biao[i]["code"], code[j]) >= 0)
                                        str += team[j]+" ";
// dui這個參數是在兑獎後加入的，這表示沒兑獎的，加入str2
                        if(!(int)all_biao[i]["dui"]) str2 += str+"\n";
// 有dui參數的，記入str1
                        else str1 += str+"\n";
                }
// 顯示信息
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
// 兑獎指令
int do_duijiang(string arg)
{
        int i, j, k, item, t;
        string result;
        object ob, me = this_player();
        mapping biao, fifa2002;

// 沒有jieguo就表示沒有開始兑獎
        if(!jieguo) return notify_fail("還未到兑獎時間！\n");
        if(!query("end_ya")) return notify_fail("還未到兑獎時間！\n");
        if(query_temp("busy")) return notify_fail("稍候........\n");
        set_temp("busy",1);
        k = 0;
// 分析指令
        if(!arg) return notify_fail("命令格式：duijiang <類別>\n");

        switch (arg)
        {
                case "1" : item = 1; t = 8; break;
                case "2" : item = 2; t = 8; break;
                case "4" : item = 4; t = 10; break;
                case "8" : item = 8; t = 20; break;
                default : return notify_fail("沒有這個項目吧！\n");
        }
        for(i=0; i<sizeof(all_biao); i++)
        {
                if ((int)all_biao[i]["type"] == item &&
                        all_biao[i]["id"] == query("id", me) )
                {
                        if (all_biao[i]["dui"] )
                                return notify_fail("你已兑過獎啦！\n");
                        result = all_biao[i]["code"];
                        j = all_biao[i]["gold"];
// 表示此人兑過獎了
                        all_biao[i]["dui"] = 1;
// 存盤
                        save();
                }
        }
        for(i=0; i<sizeof(end_biao); i++)
        {
                if ((int)end_biao[i]["type"] == item &&
                        result == end_biao[i]["code"])
                {
                        k = j * t;
                }
        }
        if(k>0)
// 中獎就給吧
        {
                write("你押 "+j+" 兩黃金，按規定得獎金 "+k+" 兩黃金，已劃入你的錢莊帳户！\n");
                addn("balance", k*10000, me);
                 message("channel:sys", HIM"【謠言】"HIR"某人："+me->name()+"兑獎得到 "+chinese_number(k)+" 兩黃金！\n"NOR, users());
                return 1;
        }
        else
// 沒有對的也來個空門獎吧
        {
                ob = new("/clone/food/jitui");
                ob->move(me);
                write("你沒押對，但發一個安慰獎，送你一根雞腿吧！\n");
                message_vision( HIY"競猜表上頭突然油光一閃，“撲”地掉下一根油光光的雞腿，正好掉進$N的手中。\n"NOR,me);
        }
        remove_call_out("enough_rest");
        call_out("enough_rest", 1);
        return 1;
}
// 對玩家輸入的國家代碼進行字母排序
string ordercode(string arg, int arg1)
{
        int i, j;
        string nc, nc1, nc2, nc3, nc4, nc5, nc6, nc7, nc8;

        j = 1;
        for (i=0; i<sizeof(code); i++)
                if (strsrch(arg, code[i]) >= 0)
                {
                        switch(j)
                        {
                                case 1 : nc1=code[i]; break;
                                case 2 : nc2=code[i]; break;
                                case 3 : nc3=code[i]; break;
                                case 4 : nc4=code[i]; break;
                                case 5 : nc5=code[i]; break;
                                case 6 : nc6=code[i]; break;
                                case 7 : nc7=code[i]; break;
                                case 8 : nc8=code[i]; break;
                        }
                        j ++;
                }
        if(arg1 == 4) nc = nc1+"-"+nc2+"-"+nc3+"-"+nc4;
        if(arg1 == 8) nc = nc1+"-"+nc2+"-"+nc3+"-"+nc4+"-"+nc5+"-"+nc6+"-"+nc7+"-"+nc8;
        return nc;
}
// 國家代碼大寫修正
string upcase(string arg)
{
        arg = replace_string(arg, "a","A");
        arg = replace_string(arg, "b","B");
        arg = replace_string(arg, "c","C");
        arg = replace_string(arg, "d","D");
        arg = replace_string(arg, "e","E");
        arg = replace_string(arg, "f","F");
        arg = replace_string(arg, "g","G");
        arg = replace_string(arg, "h","H");
        arg = replace_string(arg, "i","I");
        arg = replace_string(arg, "j","J");
        arg = replace_string(arg, "k","K");
        arg = replace_string(arg, "l","L");
        arg = replace_string(arg, "m","M");
        arg = replace_string(arg, "n","N");
        arg = replace_string(arg, "o","O");
        arg = replace_string(arg, "p","P");
        arg = replace_string(arg, "q","Q");
        arg = replace_string(arg, "r","R");
        arg = replace_string(arg, "s","S");
        arg = replace_string(arg, "t","T");
        arg = replace_string(arg, "u","U");
        arg = replace_string(arg, "v","V");
        arg = replace_string(arg, "w","W");
        arg = replace_string(arg, "x","X");
        arg = replace_string(arg, "y","Y");
        arg = replace_string(arg, "z","Z");
        return arg;
}
// 國家代碼和中文國家名的變換
string codetoteam(string arg)
{
        int i;

        for (i=0; i<sizeof(team); i++)
                if (code[i] == arg)
                        return team[i];
        return "未知國名";

}