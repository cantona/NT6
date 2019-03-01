// pai21.c 21點牌
// make by 貓部貓(Catyboy)

#include <ansi.h>
#define MAX_PAI  52

inherit ITEM;

int has_start;
mapping player;                        // 玩家ID
mapping player_data;

// 參數
int game_start;                        // 1局是否開始?
string who_play;                // 正在出牌的人

// 牌容器
int remain;                                // 所剩的牌數量
mixed pai_on_desk;                // 可以使用的牌                
mapping player_hand;        // 玩家手上的牌

// 計數器
mapping counter = ([]);

string *suit_str = ({  WHT"方塊"NOR , HIB"梅花"NOR ,HIR"紅桃"NOR , HBWHT BLK"黑桃"NOR});
string *suit_char = ({ "D","C","H","S"});
string *rank_str = ({ "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" });

int pai_number(int pai);
int pai_color(int pai);
object get_player(string id);
int is_playing(object ob);
int sizeof_pai(mixed* p);
void restore_player_data();
int pick_out();
int pick_in(string to, int card);
string id_to_pai(int id);
int do_pass(string arg);
int do_nextone(string arg);
string view_pai(string which);
void finish_21();
int auto_order();

void msg(object me,object who,string msg)
{
        if(me)
                message_vision(msg,me,who);
        else
                tell_room(environment(this_object()),msg,0);
}

int c21(mixed* inv)
{
        int i,j,sum,temp;

        sum = 0;
        temp = 0;
        for(i=0;i<inv[0];i++)
        {
                j = pai_number(inv[i+1]);
                if(j == 14)
                {
                        temp ++;
                        j = 11;
                }
                else
                        j = (j>10?10:j);
                sum+=j;
        }
                        
        for(;sum>21&&temp>0;temp--)
                sum -= 10;

        return sum;
}

void reset_pai()
{
        // 重置牌（牌盒，玩家的牌)
        int i;
        string* key;
        
        for(i=0;i<MAX_PAI;i++)
                pai_on_desk[i]=i;
        remain=MAX_PAI;

        key = keys(player);
        for(i=0;i<sizeof(key);i++)
                player_hand[key[i]]=allocate(MAX_PAI);

        who_play = 0;
}

int reset_all()
{
        // 重置整個遊戲
        int i;

        has_start = 0;
        if(sizeof(player)!=0)
                msg(this_player(),0,"$N重新置牌了。\n");
        
        player = ([]);
        player_hand = ([]);

        pai_on_desk = allocate(MAX_PAI);
        reset_pai();
        counter = ([]);

        return 1;
}

void create()
{
        set_name("21點牌桌", ({"card desk","pai","pai21"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一張桌子，上面放著一些牌，使用方法請使用(helppai)命令。\n");
                set("unit", "張");
                set("value", 1);
        }
        player = ([]);
        reset_all();
}

void init()
{
        // 幫助
        add_action("do_help", "helppai");

        // 基本指令
    add_action("do_reset", "reset");                // 重置整個遊戲
        add_action("do_restart", "restart");        // 重新遊戲
        add_action("do_join", "join");                        // 加入牌局
        add_action("do_start", "start");                // 開始遊戲
        
        add_action("do_xipai", "xipai");                // 洗牌
        add_action("do_view", "view");                        // 看牌
                
        add_action("do_nextone", "next");                // 催促下一個
        add_action("do_pass", "pass");                        // 不要牌
        
        // 擴展指令
        add_action("do_chupai", "play");                // 玩
        add_action("do_daopai", "daopai");                // 倒牌

        // 計數器
        add_action("do_showc", "showc");                // 顯示計數器
}

int do_reset(string arg)
{
        if(arg == "counter")
        {
                if(!is_playing(this_player()))
                        return notify_fail("你都不玩牌啊！\n");

                msg(this_player(),0,"$N復位計數器了。\n");
                counter = ([]);
                return 1;
        }
        if(!this_object()->id(arg))
                return 0;
                
        return reset_all();
}

int do_restart(string arg)
{
        int i;
        string* key;

        if(!is_playing(this_player()))
                return notify_fail("你都不玩，開始什麼啊！\n");

        if(!has_start)
                return notify_fail("遊戲還沒有開始。\n");

        if(sizeof(player)!=0)
                msg(this_player(),0,"$N開始新的一輪牌局了。\n\n");

        reset_pai();
        restore_player_data();
        msg(0,0,"在開始遊戲之前(play)，請各位洗牌(xipai)。\n");
        return 1;
}

int do_join(string arg)
{
        object me;

        me = this_player();
        if(has_start)
                return notify_fail("牌局已經開始，不能加入了。\n");
        if(is_playing(me))
                return notify_fail("你已經參加了。\n");
        
        // add player
        player[me->query("id")]="yes";
        player_hand[me->query("id")]=allocate(MAX_PAI);
        msg(me,0,"$N加入牌局了。\n");
        return 1;
}

int do_start(string arg)
{
        if(!is_playing(this_player()))
                return notify_fail("你都不玩，開始什麼啊！\n");
        
        if(has_start)
                return notify_fail("牌局已經開始了。\n");

        has_start = 1;
        msg(this_player(),0,"$N開始了牌局。\n\n");
        auto_order();
        msg(0,0,"在開始遊戲之前(play)，請各位洗牌(xipai)。\n");
        return 1;
}

int do_xipai(string arg)
{
        int i,sum,rand,which,temp;
        mixed* pai;

        if(!is_playing(this_player()))
                return notify_fail("你都不玩，洗什麼牌啊！\n");
        
        pai = pai_on_desk;
        sum = remain;
        rand = sum;
        
        for(i=0;i<sum;i++)
        {
                which = random(rand);
                temp = pai[rand-1];
                pai[rand-1] = pai[which];
                pai[which] = temp;
                rand --;
        }
        msg(this_player(),0,"$N洗了洗桌面的牌。\n");
        return 1;
}

int do_chupai(string arg)
{
        int i,sum,j,done,temp,id;
        mixed* inv;
        string cmd;
        object ob;
                
        if(!is_playing(this_player()))
                return notify_fail("你都不玩啊！\n");

        if(who_play==0)
                who_play = this_player()->query("id");

        if(who_play!=this_player()->query("id"))
                return notify_fail("還沒有輪到到你啊。\n");

        done = 0;
                
        if((id = pick_out())==-1)
                return 0;

        if(!pick_in(this_player()->query("id"),id))
                return 0;

        msg(this_player(),0,"$N摸了一張"+id_to_pai(id)+"。\n");

        done = 1;

        // check is over 21,if over pass
        inv = player_hand[this_player()->query("id")];
        sum = c21(inv);
                        
        msg(this_player(),0,"$N手上有"HIY+sum+"點"NOR"了。\n");
        if(sum>21)
        {
                do_pass(HIR"爆了！！！"NOR"\n");
                return 1;
        }
        
        ob = get_player(player[who_play]);
        if(ob)
        {
                who_play = player[who_play];
                do_nextone("");
        }
        return 1;
}

int do_view(string arg)
{
        mixed* pai;
        string hand_name;

        if(arg==""||arg==0)
                arg = this_player()->query("id");
        else
                hand_name = arg;
        
        pai = player_hand[arg];
        if(pai==0)
                return notify_fail("牌局沒有這個玩家。\n");
        
        if(hand_name)
                write(hand_name+"：");
        write(view_pai(arg)+"\n");
        return 1;
}

string extra_long()
{
        object me,who;
        string r,key;
        mixed *idx;
        int i;

        me = this_player();
        idx = keys(player);
        
        r = sprintf("牌盒裡面有%d張牌\n",remain);
        
        if(sizeof(player)>0)
        {
                r+="******************************************\n";
                for(i=0;i<sizeof(idx);i++)
                {
                        key = idx[i];
                        who = get_player(key);
                        if(who)
                                r = r + key + "："+view_pai(key)+"\n";
                }
                r = r + "******************************************\n";
        }
        return r;
}

int pick_out()
{
        int s,id;
                
        if(remain>0)
        {
                remain--;
                s = remain;
                id = pai_on_desk[s];
                pai_on_desk[s]=-1;
                return id;
        }
        else
        {
                msg(0,0,"沒有牌了");
                return -1;
        }
}

int pick_in(string to, int card)
{
        int s;
        mixed* pai;
                
        pai = player_hand[to];
        s = pai[0];
        s++;
        pai[s]=card;
        pai[0]++;
        return 1;
}

object get_player(string id)
{
        if(stringp(player[id]))
                return find_player(id);
        return 0;
}

int is_playing(object ob)
{
        int i;
        string id;
        id = ob->query("id");
        if(stringp(player[id]))
                return 1;
        return 0;
}

int sizeof_pai(mixed* p)
{        
        return p==0?0:p[0];
}

string view_pai(string which)
{
        mixed* pai;
        int show_all,i,j;
        string s,p;

        pai = player_hand[which];

        if(pai==0)
                return 0;
 
        if(sizeof_pai(pai)==0)
                return "沒有牌";

        s = "";
        for(i=0;i<pai[0];i++)
        {
                p = id_to_pai(pai[i+1]);
                s+= p +" ";
        }
        return sprintf("%s：%d點",s,c21(pai));
}

int do_nextone(string arg)
{
        object ob;
        string id;

        if(!is_playing(this_player()))
                return notify_fail("你都不玩牌啊！\n");

        if(who_play==0)
                return notify_fail("現在是誰出牌啊？\n");

        id = who_play;
        ob = get_player(id);
        
        if(ob==0)
                return msg(0,0,"有玩家缺場了，請重新開始遊戲(reset pai)。\n");

        if(this_player()->query("id")!=id)
                msg(this_player(),ob,"$N對$n說道：到你了。\n");
        else
                msg(this_player(),0,"對自己說道：到我啦！\n");
        return 1;
}

int do_pass(string arg)
{
        string old,str;
        string* key;
        mixed* inv;
        int i,temp;

        if(!is_playing(this_player()))
                return notify_fail("你都不玩牌啊！\n");

        if(who_play!=this_player()->query("id"))
                return notify_fail("還沒有到你啊！\n");

        if(!arg)
                arg = "ＰＡＳＳ！！";
        msg(this_player(),0,"$N說道："+arg+"\n");
        old = who_play;
        who_play = player[who_play];

        key = keys(player);

        for(i=0;i<sizeof(key);i++)
                if(player[key[i]]==old)
                        player[key[i]] = player[old];
        player[old] = "";
                                
        if(player[who_play] == "")
        {
                msg(0,0,"大家都不要了。\n");
                finish_21();
                return 1;
        }
        do_nextone("");
        return 1;
}

string id_to_pai(int id)
{
        int i,j;
        if(id <0)
                return HIR"???"NOR;
        if(id == 52)
                return HIY"小鬼"NOR + "JS";
        if(id>=53)
                return HIY"大鬼"NOR + "JB";
        i = id/13;
        j = id-i*13;
        return suit_str[i] + suit_char[i] + rank_str[j];
}

int pai_to_id(string id)
{
        int ic1=-1,ic2=-1;
        string c1,c2;
        c1 = id[0..0];
        c2 = id[1..sizeof(id)-1];

        if(c1=="J")return c2=="S"?52:53;
        if(c1==suit_char[0]) ic1=0;
        if(c1==suit_char[1]) ic1=1;
        if(c1==suit_char[2]) ic1=2;
        if(c1==suit_char[3]) ic1=3;
        if(ic1==-1)return -1;

        if(sscanf(c2,"%d",ic2)!=1)
        {
                if(c2 == "J") ic2 = 11;
                if(c2 == "Q") ic2 = 12;
                if(c2 == "K") ic2 = 13;
                if(c2 == "A") ic2 = 14;
                if(ic2==-1) return -2;
        }
        ic2 -=2;
        return ic1*13+ic2;
}

int auto_order()
{
        int i;
        string* key;
        string who,start_one;

        key = keys(player);

        start_one = key[0];
        who = "";
        for(i=0;i<sizeof(key);i++)
        {
                if(get_player(key[i]))
                {
                        if(who =="")
                                who = key[i];
                        else
                        {
                                player[who] = key[i];
                                who = key[i];
                        }
                }
        }
        player[who] = start_one;
        return 1;
}

int do_showc(string arg)
{
        string r;
        mixed *idx;
        int i;

        idx = keys(counter);
        
        r = "計數表(Scoreboard)\n－－－－－－－－－－－－－－－－－\nID　　　　　　　　分數\n－－－－－－－－－－－－－－－－－\n";
        for(i=0;i<sizeof(idx);i++)
                r = sprintf("%s%-14s%10d\n", r,idx[i],counter[idx[i]]);
        r += "－－－－－－－－－－－－－－－－－\n";

        msg(0,0,r);
        return 1;
}

void press_counter(string id,int num)
{
        counter[id]=counter[id]+num;
}

int do_daopai(string arg)
{
        int i,id;
        
        if(!is_playing(this_player()))
                return notify_fail("你都不玩，搞什麼啊！\n");

        if(!has_start)
                return notify_fail("遊戲還沒有開始。\n");

        if(remain>0)
        {
                id = pai_on_desk[0];
                for(i=1;i<remain;i++)
                        pai_on_desk[i-1] = pai_on_desk[i];
                pai_on_desk[remain-1] = id;
                msg(this_player(),0,"$N倒了一下牌。\n");
                return 1;
        }
        else
                return notify_fail("沒有牌了。\n");
}

int pai_number(int pai)
{
        if(pai==52)
                return 15;
        if(pai==53)
                return 16;
        return pai-pai/13*13+2;
}

int pai_color(int pai)
{
        if(pai>=52)
                return 5;
        return pai/13+1;
}

void save_player_data()
{
        string* inv;
        int i;
        inv = keys(player);
        player_data = ([]);
        for(i=0;i<sizeof(inv);i++)
                player_data[inv[i]] = player[inv[i]];
}

void restore_player_data()
{
        int i;
        string* key;

        if(!player_data)
                return;

        key = keys(player_data);
        for(i=0;i<sizeof(key);i++)
                player[key[i]] = player_data[key[i]];
}

int sort_21(string str1, string str2)
{
        int c1,c2;
        string temp;

        sscanf(str1,"%s:%d",temp,c1);
        sscanf(str2,"%s:%d",temp,c2);
        
        if(c1==c2)
                return 0;

        if(c1>21&&c2>21)
                return (c1<c2)?-1:1;

        if(c1>21)
                c1 = -1;
        if(c2>21)
                c2 = -1;
        return (c1>c2)?-1:1;
}

void finish_21()
{
        string* key;
        mixed* inv2;
        mixed* inv;
        string str,r,id;
        int i,maxn,fen,k,lpoint;

        key = keys(player);
        inv2 = allocate(sizeof(player));
        for(i=0;i<sizeof(key);i++)
        {
                str = key[i];
                inv2[i] = str + ":" + c21(player_hand[str]);
        }
                
        inv = sort_array(inv2,"sort_21",this_object());
        
        lpoint = -1;
        r = "結果\n－－－－－－－－－－－－－－－－－\nID　　　　　　　　點數       得分\n－－－－－－－－－－－－－－－－－\n";
        for(i=0;i<sizeof(inv);i++)
        {
                sscanf(inv[i],"%s:%d",id,k);
                if(k != lpoint)
                {
                        fen = sizeof(inv) - i - 1;
                        lpoint = k;
                }
                if(i==0)maxn=k;
                if(k==maxn)r+=HIY;
                if(k>21)
                {
                        r+=HIR;
                        fen = 0;
                }
                r = sprintf("%s%-14s%5d%12d\n", r,id,k,fen);
                r+=NOR;

                press_counter(id,fen);
        }
        r += "－－－－－－－－－－－－－－－－－\n\n";
        msg(0,0,r);
        
        reset_pai();
        restore_player_data();
        msg(0,0,"請各位重新洗牌(xipai)開始新的一局。\n");
}

int do_help(string arg)
{
        this_player()->start_more( @HELP
玩21點牌桌使用方法:
──[開始遊戲]───────────────
幫助命令：helppai
加入命令：join　　　　　加入遊戲
開始命令：start 　　　　開始以後不能再加入
重置命令：reset pai 　　結束遊戲

──[遊戲命令]───────────────
重新遊戲：restart
　　摸牌：play　　　　　進行遊戲
不再要牌: pass

──[其它命令]───────────────
洗牌命令：xipai
看牌命令：view [玩家ID] 觀察玩家手上的牌
催促命令：next　　　　　催促正在出牌的人

──[計數牌使用]──────────────
顯示: showc
重置: reset counter




──[遊戲規則]───────────────
遊戲開始以後，每人輪流摸牌直到不摸為止。
最後根據每人手上的點數決定勝負。
點數 > 21 為輸，點數<21的時候點數大者勝。
J，Q，k為10點，A可以為1點或者為11點。

──────────────────────
                        make by 貓部貓(Catyboy) v1.0
HELP
        );
        return 1;
}

mixed t()
{
        return pai_on_desk;
}
