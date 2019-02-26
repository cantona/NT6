// dahuashaizi.c

#include <ansi.h>

#define MAX_SE                6
#define MAX_TOSS        5

inherit ITEM;

int has_start;
int has_guess;
int se_num;                                // 每人的骰子數量
int se_total;                                // 每人的骰子數量2
int cur_point;                                // 當前的點數
int cur_amount;                                // 當前的數量
int has_guess_one;                        // 是否猜過１
string cur_player;                        // 當前的玩家ID
string last_player;                        // 上一個玩家
string who_lost;                        // 輸方
mapping player;                                // 兩個玩家 [id:({骰，骰...})]
mapping player_deal;                        // 完成的玩家
mapping player_toss;                        // 玩家toss次數
mapping player_follow;                        // 玩家順序
mapping visitor;                        // 觀戰的人 [id:({id,...})]
mapping counter = ([]);                        // 計數器
mixed        history;                        // 歷史 string
int reset_game(int all);

mixed se_text = ({
        ({"","","","",""}),
        ({
                "┌───┐",
                "│      │",
                "│  ●  │",
                "│      │",
                "└───┘",
        }),
        ({
                "┌───┐",
                "│  ●  │",
                "│      │",
                "│  ●  │",
                "└───┘",
        }),
        ({
                "┌───┐",
                "│●　　│",
                "│　●　│",
                "│　　●│",
                "└───┘",
        }),
        ({
                "┌───┐",
                "│●　●│",
                "│　　　│",
                "│●　●│",
                "└───┘",
        }),
        ({
                "┌───┐",
                "│●　●│",
                "│　●　│",
                "│●　●│",
                "└───┘",
        }),
        ({
                "┌───┐",
                "│●　●│",
                "│●　●│",
                "│●　●│",
                "└───┘",
        })
});

void msg(object me,object who,string msg)
{
        if(me)
                message_vision(msg,me,who);
        else
                tell_room(environment(this_object()),msg,0);
}

object get_player(string id)
{
        object ob;
        ob= find_player(id);
        if( !ob || environment(ob) != environment(this_object()) )
                return 0;
        return ob;
}

object get_cur_player()
{
        return get_player(cur_player);
}

int is_playing(object ob)
{
        string id;
        id=query("id", ob);
        if(undefinedp(player[id]))
                return 0;
        return 1;
}

mixed get_se(int num)
{
        return se_text[num];
}

void create()
{
        set_name("大話骰台", ({ "dahua desk", "desk"}) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else
        {
                set("unit", "張");
                set("long", "這是一張大話骰台，玩家可以在上面玩大話骰子。\n");
                set("value", 1);
                set("material", "wood");
        }

        se_total = 5;
        reset_game(1);
        setup();
}

string for_other_msg(object who)
{
        object ob;
        string m;

        m = "";
        if(has_guess&&last_player)
        {
                ob = get_player(last_player);
                if(ob)
                {
                        m=sprintf("%s\n%s(%s)猜骰子數為：%d個%d\n",m,query("name", ob),query("id", ob),cur_amount,cur_point);
                        if(ob!=who)
                                m=m+"如果你不相信，可以拆穿大話("HIY"dahua"+query("id", ob)+NOR")\n";
                }
        }
        return m;
}

string for_guess_msg()
{
        string m;

        m = "";
        if( has_guess&&last_player )
                m=m+for_other_msg(0)+"否則";
        m = m+"你的猜測是("HIY"guess 骰子數目 骰子點數"NOR")？\n";
        if(has_guess&&last_player)
                m = m+"注意：" HIC "骰子數目或者骰子點數必須比前一位玩家大。\n"NOR;
        return m;
}

int is_visitor(object who,string which)
{
        if(!get_player(which))
                return 0;

        if( !visitor[which] || member_array(query("id", who),visitor[which]) == -1 )
                return 0;
        return 1;
}

string build_se(object who)
{
        mixed *s;
        string r,t;
        int i,y,num;
        object ob;

        if(!who)
                return "";

        r = "";
        if( s=player[query("id", who)] )
        {
                for(y=0;y<5;y++)
                {
                        t = "";
                        for(i=0;i<sizeof(s);i++)
                        {
                                num = s[i];
                                t = t + se_text[num][y] + "　";
                        }
                        r = r + t + "\n";
                }
                if(has_guess&&last_player)
                        r = r + for_other_msg(who);
        }
        return r;
}

void toss(object ob)
{
        int i;
        mixed* s;

        if(!ob)
                return;
        if(s = player[query("id",ob)]) 
        {
                for(i=0;i<sizeof(s);i++)
                        s[i] = random(6)+1;
        }
        player[query("id",ob)] = sort_array(s,1); 
}

int auto_order()
{
        int i;
        string* key;
        string who,start_one;

        key = keys(player);
        player_follow = ([]);
        who = "";
        for(i=0;i<sizeof(key);i++)
        {
                if(get_player(key[i]))
                {
                        if(!start_one)
                                start_one = key[i];
                        if(who =="")
                                who = key[i];
                        else
                        {
                                player_follow[who] = key[i];
                                who = key[i];
                        }
                }
        }
        player_follow[who] = start_one;
        return 1;
}

int reset_game(int all)
{
        int i;
        string* idx;
        object ob;

        if(all)has_start = 0;
        has_guess = 0;
        se_num = se_total;
        cur_point = 0;
        cur_amount = 0;
        cur_player = 0;
        has_guess_one = 0;
        last_player = 0;
        if(all)who_lost = 0;
        if(all)player = ([]);
        player_deal = ([]);
        player_toss = ([]);
        player_follow = ([]);
        if(all)visitor = ([]);
        if(all)counter = ([]);
        history = 0;
        if(!all)
        {
                idx = keys(player);
                for(i=0;i<sizeof(idx);i++)
                {
                        if(ob = get_player(idx[i]))
                        {
                                player[idx[i]] = allocate(se_num);
                                toss(ob);
                        }
                        else
                                map_delete(player,idx[i]);
                }
                auto_order();
        }
        return 1;
}

string extra_long()
{
        object who;
        string r;
        mixed *idx;
        int i;
        
        if(sizeof(player)>0)
        {
                idx = keys(player);
                r =        "******************************************\n";
                for(i=0;i<sizeof(idx);i++)
                {
                        who = get_player(idx[i]);
                        if(who) r = r + who->short() + "\n";
                }
                r += "******************************************\n";
        }
        return r;
}

int view_se(object who,object bsee)
{
        if(who)
        {
                if(bsee)
                        tell_object(bsee,build_se(who));
                else
                        tell_object(who,build_se(who));
        }
        return 1;
}

void start_game(int num)
{
        if(num>1&&num<=MAX_SE)
                se_total = num;
        reset_game(0);
        has_start = 1;
        msg(0,0,"開始遊戲了。\n");
}

void init()
{

//        add_action("do_help","helpse");                        // 幫助

        add_action("do_reset","reset");                        // 重置遊戲
        add_action("do_start","start");                        // 重新開始
        add_action("do_join","join");                        // 加入遊戲

        add_action("do_toss","toss");                        // 搖骰子
        add_action("do_view","view");                        // 查看情況
        add_action("do_finish","finish");                // 完成
        add_action("do_finish","deal");                        // 完成

        add_action("do_dahua","dahua");                        // 發現大話
        add_action("do_guess","guess");                        // 猜測
        add_action("do_guess","g");                                // 猜測

        add_action("do_next","next");                        // 催促
        add_action("do_showc","showc");                        // 顯示計數器
        add_action("do_visitor","visit");                // 增加旁觀者
        add_action("do_history","history");                // 查看猜測歷史
}

int do_toss(string arg)
{
        object me,v;
        string* idx;
        int i;

        me = this_player();

        if(!is_playing(me))
                return notify_fail("你都不玩啊！\n");
        if(!has_start)
                return notify_fail("遊戲還沒有開始了。\n");
        if(has_guess)
                return notify_fail("已經開始猜骰子了。\n");
        if(player_toss[query("id",me)]>=MAX_TOSS) 
                return notify_fail(sprintf("你已經搖過%d次了。\n",MAX_TOSS));

        toss(me);
        player_toss[query("id",me)]++; 
        msg(me,0,"$N拿起骰子在手中搖了兩搖。\n");
        view_se(me,0);

        if(idx = visitor[query("id",me)]) 
        {
                for(i=0;i<sizeof(idx);i++)
                {
                        v = get_player(idx[i]);
                        if(v)
                                view_se(me,v);
                }
        }        
        return 1;
}

int do_reset(string arg)
{
        int i;
        mixed* idx;

        if(!this_object()->id(arg))
                return 0;

        if(!is_playing(this_player()))
        {
                idx = keys(player);
                for(i=0;i<sizeof(idx);i++)
                {
                        if(get_player(idx[i]))
                                return notify_fail("你都不玩啊！\n");
                }
        }
                
        reset_game(1);
        msg(this_player(),0,"$N重置了遊戲。\n");
        return 1;
}

int do_start(string arg)
{
        int i;

        if(!is_playing(this_player()))
                return notify_fail("你都不玩啊！\n");

        if(sizeof(player)<2)
                return notify_fail("至少要兩個人才能玩。\n");

        if(!arg||sscanf(arg,"%d",i)!=1)
                i = 0;
        else
        {
                if(i<1||i>MAX_SE)
                        return notify_fail(sprintf("start [骰子數目]  *注意* 骰子數目必須>1並且<=%d\n",MAX_SE));
        }
        start_game(i);
        return 1;
}

int do_view(string arg)
{
        object me;
        object ob;

        me = this_player();
        
        if(!is_playing(me))
        {
                if(arg&&(ob = get_player(arg)))
                        if(!is_visitor(me,arg))
                                ob = 0;

                if(!ob)
                        return notify_fail("你都不玩啊！\n");
        }
        else
                ob = me;
        
        view_se(ob,me);
        return 1;
}

int do_join(string arg)
{
        object me;

        me = this_player();
        if(has_start)
                return notify_fail("遊戲已經開始，不能加入了，請使用(reset)命令重置。\n");
        if(is_playing(me))
                return notify_fail("你已經參加了。\n");

        player[query("id",me)]=allocate(se_num); 
        toss(me);
        msg(me,0,"$N加入遊戲了。\n");
        return 1;
}

int do_next(string arg)
{
        object ob;
        object me;
        
        me = this_player();
        if(!is_playing(me))
                return notify_fail("你都不玩啊！\n");

        if(!has_guess)
                return notify_fail("還沒有開始猜骰子了。\n");
        if(!cur_player)
                return notify_fail("現在是誰猜啊？\n");

        ob = get_cur_player();
        
        if(ob==0)
        {
                msg(0,0,"有玩家缺場了，請重新開始遊戲(start)。\n");
                return 1;
        }

        if(me!=ob)
                msg(me,ob,"$N對$n説道：到你了。\n");
        else
                msg(me,0,"對自己説道：到我啦！\n");
        tell_object(ob,for_guess_msg());
        return 1;
}

int do_guess(string arg)
{
        int n,p,ok;
        object ob;
        object me;
        string nextone;
        
        me = this_player();
        if(!is_playing(me))
                return notify_fail("你都不玩啊！\n");

        if(!has_guess)
                return notify_fail("還沒有開始猜骰子了。\n");
        ob = get_cur_player();
        if(ob!=me)
                return notify_fail("還沒有到你猜了。\n");

        if(!arg||sscanf(arg,"%d %d",n,p)!=2)
                return notify_fail("guess 骰子數目 骰子點數\n");

        if(n<sizeof(player)||p>6||p<=0)
                return notify_fail(sprintf("骰子數目必須>=%d，骰子點數必須>0並且<=6\n",sizeof(player)));

        ok = 1;
        if(last_player)
        {
                if(n>cur_amount)
                        ok = 1;
                else
                {
                        if(n==cur_amount)
                        {
                                if(p>cur_point)
                                        ok = 1;
                                else
                                        ok = 0;
                        }
                        else
                                ok = 0;
                }
        }
        if(!ok)
                return notify_fail("骰子數目或者骰子點數必須比前一位玩家大。\n");

        last_player=query("id", me);
        cur_amount = n;
        cur_point = p;
        if(p==1)has_guess_one = 1;

        cur_player = player_follow[last_player];

        msg(me,0,sprintf("$N(%s)説道：%d個%d\n",query("id", me),n,p));
        if(history)
                history=history+({sprintf("%-20s：%d個%d",query("name", me)+"("+query("id", me)+")",n,p)});
        else
                history=({sprintf("%-20s：%d個%d",query("name", me)+"("+query("id", me)+")",n,p)});

        do_next("");
        return 1;
}

void add_counter(string who,int number)
{
        counter[who] = counter[who]+number;
}

int show_all_se(object who)
{
        string* idx;
        mixed* s;
        int i,j,p,sc,pt;
        object ob;

        int c;
        string m,o;

        if(!last_player)return 0;
        ob = get_player(last_player);
        if(!ob||!who)return 0;

        has_guess = 0;
        
        idx = keys(player);
        c = 0;
        m = "";
        for(i=0;i<sizeof(idx);i++)
        {
                if(get_player(idx[i]))
                {
                        s = player[idx[i]];
                        m = sprintf("%s%12s：",m,idx[i]);
                        o = "";
                        sc = 0;
                        for(j=0;j<se_num;j++)
                        {
                                m = sprintf("%s%d",m,s[j]);
                                p = s[j];
                                if(p==1&&!has_guess_one)p = cur_point;
                                if(p==cur_point)
                                {
                                        c ++;
                                        sc ++;
                                        o = sprintf("%s%d",o,s[j]);
                                }
                        }
                        if(sc==se_num)
                        {
                                o = o + " 圍骰+1";
                                c++;
                        }
                        m = m + "||"+o+"\n";
                }
        }
        m=sprintf("%s%s猜有"HIC"%d"NOR"個%d，",m,query("name", ob),cur_amount,cur_point);
        m = sprintf("%s現在有"HIC"%d"NOR"個%d\n\n",m,c,cur_point);
        msg(0,0,m);

        if( query("id", who) == cur_player )
                pt = 1;
        else
                pt = 2;

        if(c<cur_amount)
        {
                add_counter(query("id", who),pt);
                add_counter(query("id", ob),-pt);
                msg(ob,who,BLINK HIY "$N被$n拆穿了大話！！！\n\n" NOR);
                who_lost = last_player;
        }
        else
        {
                add_counter(query("id", who),-pt);
                add_counter(query("id", ob),pt);
                msg(who,0,BLINK HIY "$N判斷錯誤了！！！\n\n" NOR);
                who_lost=query("id", who);
        }
        start_game(0);
}

int do_dahua(string arg)
{
        object ob;
        object me;
        
        me = this_player();

        if(!arg)
        {
                msg(me,0,"$N一扁嘴嘟囔道：“大話精，大話精...”\n");
                return 1;
        }

        if(!is_playing(me))
                return notify_fail("你都不玩啊！\n");

        if(!has_guess||!last_player)
                return notify_fail("還沒有開始猜骰子了。\n");
        
        ob = get_player(last_player);
        if(ob==me)
                return notify_fail("自己不相信自己。\n");

        if(last_player!=arg)
                return notify_fail("不是他最後猜骰子了。\n");

        msg(me,ob,HIC "\n$N對$n説道：我不相信！！！\n" NOR);
        show_all_se(me);
        return 1;
}

int do_finish(string arg)
{
        object me,ob;

        me = this_player();
        if(!is_playing(me))
                return notify_fail("你都不玩啊！\n");
        if(!has_start)
                return notify_fail("遊戲還沒有開始了。\n");
        if(has_guess)
                return notify_fail("已經開始猜骰子了。\n");

        player_deal[query("id",me)] = 1; 
        msg(me,0,"$N準備好了。\n");
        if(sizeof(player_deal)==sizeof(player))
        {
                // all is finish
                has_guess = 1;
                msg(0,0,"\n猜骰子開始\n");
                if(who_lost)cur_player = who_lost;
                who_lost = 0;
                if( !cur_player)cur_player=query("id", me);
                if(ob = get_cur_player())
                {
                        msg(ob,0,"$N説道：由我先猜！！！\n");
                        tell_object(ob,for_guess_msg());
                }
                else
                        msg(0,0,"缺少了"+cur_player+"，不能進行遊戲，請重新開始(start)\n");
        }
        
        return 1;
}

int do_history(string arg)
{
        if(!history)
                tell_object(this_player(),"沒有歷史資料。\n");
        else
                tell_object(this_player(),implode(history,"\n")+"\n");
        return 1;
}

int do_showc(string arg)
{
        string r;
        string* idx;
        int i;

        if(!counter) return 0; 

        idx = keys(player);
        
        r = "計數表(Scoreboard)\n－－－－－－－－－－－－－－－－－\nID　　　　　　　　分數\n－－－－－－－－－－－－－－－－－\n";
        for(i=0;i<sizeof(idx);i++)
        {
                if(get_player(idx[i]))
                        r = sprintf("%s%-14s%10d\n", r,idx[i],counter[idx[i]]);
        }
        r += "－－－－－－－－－－－－－－－－－\n";

        msg(0,0,r);
        return 1;
}

int do_visitor(string arg)
{
        string key;
        object me,ob;
        int del;

        if(!arg)
                return notify_fail("visit [-d] 玩家ID\n");

        if(sscanf(arg, "-d %s", key)==1 )
                del = 1;
        else
        {
                del = 0;
                key = arg;
        }
                
        me = this_player();
        if(is_playing(me))
        {
                ob = present(key,environment(this_object()));
                if(!ob)
                        return notify_fail("這裏沒有這個玩家啊？\n");

                if(del)
                {
                        if( !is_visitor(ob,query("id", me)) )
                                return notify_fail("不是你的觀戰者。\n");

                        msg(me,ob,"$N不再允許$n觀看$N的戰況。\n");
                        visitor[query("id", me)]=visitor[query("id", me)]-({query("id", ob)});
                }
                else
                {
                        if( is_visitor(ob,query("id", me)) )
                                return notify_fail("已經是你的觀戰者了。\n");

                        msg(me,ob,"$N讓$n觀看$N的戰況。\n");
                        if( !visitor[query("id", me)] )
                                visitor[query("id", me)]=({query("id", ob)});
                        else
                               visitor[query("id",me)]+=query("id", ob);
                }
        }
        else
        {
                if(del)
                        return notify_fail("？？？？\n");

                ob = get_player(key);
                if(!ob)
                        return notify_fail("沒有這個玩家在玩啊？\n");
                msg(me,ob,"$N希望成為$n的觀戰者。\n");
                tell_object(ob,"接受使用[visit"+query("id", me)+"]。\n");
        }
        return 1;
}

int do_help(string arg)
{
        this_player()->start_more( @HELP
大話骰使用方法:
——[開始遊戲]———————————————
幫助命令：helpse
加入命令：join　　　　　加入遊戲
開始命令：start 　　　　開始遊戲
重置命令：reset se                結束遊戲

——[遊戲前命令]———————————————
　搖骰子：toss
查看骰子：view [玩家ID]
準備結束：finish 或者 deal

——[遊戲命令]———————————————
拆穿大話：dahua 玩家ID
猜測骰子：guess 骰子數量 骰子點數
　　　　　或者 g 骰子數量 骰子點數
催促玩家：next

——[其它命令]———————————————
　計數器：showc
猜測日誌：history

——[旁觀命令]———————————————
觀戰命令：visit [-d] 玩家ID
                邀請其它玩家觀看你的遊戲。
                加參數 -d 表示刪除該玩家的觀看資格。

——[遊戲規則]———————————————
建設中...

——————————————————————
                        make by 貓部貓(Catyboy) v1.0
HELP
        );
        return 1;
}