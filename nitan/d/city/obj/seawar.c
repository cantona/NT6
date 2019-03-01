// seaf.c 海戰棋

#include <ansi.h>

#define WIDTH        9
#define HEIGHT        9
#define SHIP_NUM        10

inherit ITEM;

int has_start;
int game_mode;                // 開始攻擊？0-布局 1-火力 2-開火 3-結束
int who_win;                // 勝利方 0=沒有結束 -1=和手
mixed table;                // 兩個棋盤 table = cell[9][9]
                        // cell = ({ HasShip , HasFire })
mapping player;                // 兩個玩家 [id:tableNumber(1,2)]
mixed player_action;        // 玩家的活動
mapping visitor;        // 兩個玩家觀戰的人 [id:({id,...})]
mixed ship;                // 兩個玩家的戰船 ({ mixed({hasDest,x,y,fireX,fireY,fireValue}) ,...})
mixed numbers = ({"０","１","２","３","４","５","６","７","８","９"});
mixed cell_status = ({
                        // 自己的棋盤
                        ({"～","＊","～"}),
                        ({"船","＠","船"}),
                        // 敵方的棋盤
                        ({"～","＊","＃"}),
                        ({"～","Ｘ","＃"})
        });                // 棋格的狀態
mixed fire_x,fire_y;
int reset_game(int all);

void msg(object me,object who,string msg)
{
        if(me) message_vision(msg,me,who);
        else tell_room(environment(this_object()),msg,0);
}

int player_id(string key)
{
        return player[key];
}

object get_player(string id)
{
        object ob;
        ob= find_player(id);
        if( !ob || environment(ob) != environment(this_object()) )
                return 0;
        return ob;
}

string enemy_id(string key)
{
        mixed *idx;
        int i;
        idx = keys(player);
        for(i=0;i<sizeof(idx);i++)
                if(idx[i]!=key)
                        return idx[i];
        return 0;
}

object get_player2(int wHIYh)
{
        mixed *idx;
        int i;

        idx = keys(player);
        for(i=0;i<sizeof(idx);i++)
                if(player[idx[i]]==wHIYh)
                        return get_player(idx[i]);
        return 0;        
}

int is_visitor(object who,string which)
{
        if(!get_player(which))
                return 0;
        if( !visitor[which] || member_array(query("id", who),visitor[which]) == -1 )
                return 0;
        return 1;
}

int is_playing(object ob)
{
        string id;
        id=query("id", ob);
        if(player[id])
                return 1;
        return 0;
}

mixed get_table(string id)
{
        int i;
        if(i=player[id])
                return table[i-1];
        return 0;
}

mixed get_ship(string id)
{
        int i;
        if(i=player[id])
                return ship[i-1];
        return 0;
}

int remain_ship(string who)
{
        int i,c;
        mixed *sh;
        sh = get_ship(who);
        c = 0;
        for(i=0;i<SHIP_NUM;i++)
                if(!sh[i][0])c++;
        return c;
}

int remain_place(string who)
{
        int i,c;
        mixed *sh;
        sh = get_ship(who);
        c = 0;
        for(i=0;i<SHIP_NUM;i++)
                if(!sh[i][1])c++;
        return c;
}

int remain_fire(string who)
{
        int i,c;
        mixed *sh;
        sh = get_ship(who);
        c = 0;
        for(i=0;i<SHIP_NUM;i++)
                if(!sh[i][0]&&!sh[i][3])c++;
        return c;
}

void create()
{
        set_name("海戰棋", ({ "seawar board","board","sea"}) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else
        {
                set("unit", "副");
                set("long", "這是一副海戰棋，上面稀稀落落擺著一些艦船。\n");
                set("value", 1);
                set("material", "wood");
        }
        reset_game(1);
        setup();
}

string player_status(string key)
{
        mixed* sh;
        int i;
        string r;

        sh = get_ship(key);

        if(!sh)
                return "???";

        r = "";
        for(i=0;i<SHIP_NUM;i++)
        {
                if(sh[i][0])
                        r+= HIR"Ｘ"NOR" ";
                else
                        r+= HIB"船"NOR" ";
        }
        return r;
}

string build_board(string key)
{
        mixed *mt,*et,*d;
        string r;
        int x,y,id,mid,eid;

        id = player_id(key);
        if(!id) return "";
        if(id==1)
        {
                mid = 0;
                eid = 1;
        }
        else
        {
                mid = 1;
                eid = 0;
        }
        mt = table[mid];
        et = table[eid];
        
        r = "\n";
        r += "＊我軍的情況＊　　　　　＊敵軍的情況＊\n";
        r += "　１２３４５６７８９　　　１２３４５６７８９\n";
        for(y=0;y<HEIGHT;y++)
        {
                r = r+numbers[y+1];
                for(x=0;x<WIDTH;x++)
                {
                        d = mt[x][y];
                        if(game_mode==2 && x==fire_x[mid]-1 && y==fire_y[mid]-1)
                                r += BLINK+HIY + cell_status[d[0]][d[1]] + NOR;
                        else r += cell_status[d[0]][d[1]];
                }

                r = r+"　　" + numbers[y+1];
                for(x=0;x<WIDTH;x++)
                {
                        d = et[x][y];
                        if(game_mode == 2 && x == fire_x[eid]-1 && y == fire_y[eid]-1)
                                r += cell_status[d[0]+2][d[1]];
                        else
                                r += cell_status[d[0]+2][d[1]];
                }
                r+="\n";
        }
        r += "船只狀態：" + player_status(key) + "\n";
        return r;
}

int reset_game(int all)
{
        int i,x,y;

        table = ({0,0});
        if(all)
        {
                player = ([]);
                visitor = ([]);
        }
        ship = ({0,0});
        player_action = ([]);

        for(i=0;i<2;i++)
        {
                table[i] = allocate(WIDTH);
                for(x=0;x<WIDTH;x++)
                {
                        table[i][x] = allocate(HEIGHT);
                        for(y=0;y<HEIGHT;y++)
                                table[i][x][y] = ({0,0});
                }
                
                ship[i] = allocate(SHIP_NUM);
                for(x=0;x<SHIP_NUM;x++)
                        ship[i][x] = ({0,0,0,0,0,0});
        }

        if(all)
                has_start = 0;
        return 1;
}

void display(int who)
{
        string b,id,m;
        int i,j;
        mixed* v;
        object ob,vtor;

        for(i=1;i<=2;i++)
        {
                if(!who||who==i)
                {
                        ob = get_player2(i);
                        if(ob)
                        {
                                id=query("id", ob);
                                b = build_board(id);
                                tell_object(ob,b);
                                v = visitor[id];
                                for(j=0;j<sizeof(v);j++)
                                {
                                        vtor = find_player(v[j]);
                                        if(vtor)//&&environment(vtor) == environment(this_object()))
                                                tell_object(vtor,b);
                                }
                                
                                switch(game_mode)
                                {
                                case 0:
                                        m=sprintf("布置船只：%d只\n",remain_place(query("id", ob)));
                                        m += "使用["HIY"place X坐標 Y坐標"NOR"]布置船只\n";
                                        m += "使用["HIY"unplace X坐標 Y坐標"NOR"]取消布置\n";
                                        m += "使用["HIY"rplace"NOR"]隨機擺放船只\n";
                                        break;
                                case 1:
                                        m=sprintf("布置火力：%d個\n",remain_fire(query("id", ob)));
                                        m += "使用["HIY"fire X坐標 Y坐標"NOR"]設置攻擊位置\n";
                                        m += "使用["HIY"unfire X坐標 Y坐標"NOR"]取消設置\n";
                                        break;
                                case 3:
                                        m = "戰鬥結束了。\n戰況：";
                                        if(who_win==-1)
                                                m+="和手";
                                        else if(who_win==i)
                                                m+=HIY"勝利了"NOR;
                                        else
                                                m+=HBWHT BLK"失敗了"NOR;
                                        break;
                                }
                                if(m)
                                        tell_object(ob,m);
                        }
                }
        }
}

string extra_long()
{
        object who;
        string r,key;
        mixed *idx;
        int i;
        
        if(sizeof(player)>0)
        {
                idx = keys(player);
                r =        "******************************************\n";
                for(i=0;i<sizeof(idx);i++)
                {
                        key = idx[i];
                        who = get_player(key);
                        if(who)
                                r = r + key + "："+player_status(key)+"\n";
                }
                r += "******************************************\n";
        }
        return r;
}

int view_board(object who,string which)
{
        string b;
        object ob;
        mixed *v;
        int i,see;

        ob = get_player(which);
        if(!ob)
                return 0;

        see = 0;
        if(ob==who)
                see = 1;

        if(!see)
                see = is_visitor(who,which);

        if(see)
        {
                b = build_board(which);
                tell_object(who,b);
                return 1;
        }
        return 0;
}

void start_game()
{
        has_start = 1;
        game_mode = 0;
        who_win = 0;

        msg(0,0,"開始遊戲\n");
        display(0);
}

int before_fire()
{
        game_mode = 1;
        player_action = ([]);
        msg(0,0,"\n\n"HIC"！！！進入戰備狀態！！！"NOR"\n\n");
        display(0);
}

int start_fire()
{
        player_action = ([]);
        msg(0,0,"\n\n"HIR"！！！開始戰鬥狀態！！！"NOR"\n\n");
        game_mode = 2;
        fire_x = ({0,0});
        fire_y = ({0,0});
        remove_call_out("fire_it");
        call_out("fire_it",2);
}

void init()
{

//        add_action("do_help","helpboard");                // 幫助

        add_action("do_reset","reset");                        // 重置遊戲
        add_action("do_start","start");                        // 重新開始
        add_action("do_join","join");                        // 加入遊戲

        add_action("do_view","view");                        // 查看情況
        add_action("do_visitor","visit");                // 查看情況
        add_action("do_finish","finish");                // 完成

        add_action("do_place","place");                        // 布置船只
        add_action("do_rplace","rplace");                // 隨機擺放船只
        add_action("do_unplace","unplace");                // 取消船只

        add_action("do_fire","fire");                        // 布置火力
        add_action("do_unfire","unfire");                // 取消火力
}

int do_reset(string arg)
{
        mixed *idx;
        int i;

        if(!this_object()->id(arg))
                return 0;

        if(!is_playing(this_player()))
        {
                if(get_player2(1)||get_player2(2))
                        return notify_fail("你都不玩啊！\n");
        }
                
        if(reset_game(1))
                msg(this_player(),0,"$N重置了遊戲。\n");
        return 1;
}

int do_start(string arg)
{
        mixed *idx;
        int i;

        if(!is_playing(this_player()))
                return notify_fail("你都不玩啊！\n");

        reset_game(0);
        start_game();
        return 1;
}

int do_view(string arg)
{
        mixed *idx;
        int i;

        if(!is_playing(this_player()))
        {
                if(!arg) return notify_fail("你都不玩啊！\n");
                if(!is_visitor(this_player(),arg))
                        return notify_fail("你不能夠看"+arg+"的棋，可以使用[visit "+arg+"]命令成為"+arg+"的觀眾。\n");
        }
        if( !arg)arg=query("id", this_player());
        if(!view_board(this_player(),arg)) return notify_fail("？？？\n");
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

        player[query("id",me)]=sizeof(player)+1; 
        msg(me,0,"$N加入遊戲了。\n");

        if(sizeof(player)==2)
                start_game();

        return 1;
}

int do_place(string arg)
{
        int i,x,y;
        mixed *sh,*tb;
        string id;

        if(!is_playing(this_player()))
                return notify_fail("你都不玩啊！\n");
        
        if(!has_start||game_mode!=0)
                return notify_fail("現在不是布置船只的時候。\n");

        if( !arg || sscanf(arg, "%d %d", x, y)!=2 )
                return notify_fail("place X坐標 Y坐標\n");

        if(x<1||x>WIDTH)
                return notify_fail("X坐標錯誤\n");
        if(y<1||y>HEIGHT)
                return notify_fail("Y坐標錯誤\n");

        id=query("id", this_player());
        sh = get_ship(id);
        tb = get_table(id);
        if(!sh||!tb)
                return notify_fail("access date fail\n");

        if(tb[x-1][y-1][0] == 1)
                return notify_fail("該處已經布置了船只\n");

        for(i=0;i<SHIP_NUM;i++)
        {
                if(!sh[i][1])
                {
                        sh[i][1] = x;
                        sh[i][2] = y;
                        tb[x-1][y-1][0] = 1;
                        break;
                }
        }

        if(i==SHIP_NUM)
                return notify_fail("你已經沒有空余的船只可以布置了。\n");
        else
        {
                display(player_id(id));
                if(!remain_place(id))
                        tell_object(this_player(),"\n使用[Finish]結束布置船只。\n");
        }
        return 1;
}

int do_unplace(string arg)
{
        int i,x,y;
        mixed *sh,*tb;

        if(!is_playing(this_player()))
                return notify_fail("你都不玩啊！\n");
        
        if(game_mode!=0)
                return notify_fail("現在不是布置船只的時候。\n");

        if( !arg || sscanf(arg, "%d %d", x, y)!=2 )
                return notify_fail("unplace X坐標 Y坐標\n");

        if(x<1||x>WIDTH)
                return notify_fail("X坐標錯誤\n");
        if(y<1||y>HEIGHT)
                return notify_fail("Y坐標錯誤\n");

        sh=get_ship(query("id", this_player()));
        tb=get_table(query("id", this_player()));
        if(!sh||!tb)
                return notify_fail("access date fail\n");

        for(i=0;i<SHIP_NUM;i++)
        {
                if(sh[i][1]==x&&sh[i][2]==y)
                {
                        sh[i][1] = 0;
                        sh[i][2] = 0;
                        tb[x-1][y-1][0] = 0;
                        display(player_id(query("id", this_player())));
                        break;
                }
        }

        if(i==SHIP_NUM)
                return notify_fail("該位置沒有布置船只。\n");
        return 1;
}

int do_finish(string arg)
{
        int i,x,y;
        mixed *sh;
        string id;

        if(!is_playing(this_player()))
                return notify_fail("你都不玩啊！\n");
        
        if(!(game_mode==0||game_mode==1))
                return notify_fail("？？？\n");

        id=query("id", this_player());
        sh = get_ship(id);
        if(!sh)
                return notify_fail("access date fail\n");

        if(game_mode==0)
        {
                if(remain_place(id))
                        return notify_fail("還有船只沒有布置\n");
        }
        else if(game_mode==1)
        {
                if(remain_fire(id))
                        return notify_fail("還有火力沒有布置\n");
        }

        if(game_mode==0)
                msg(this_player(),0,"$N的船只布置完成\n");
        else if(game_mode==1)
                msg(this_player(),0,"$N的火力布置完成\n");

        player_action[query("id", this_player())]=1;
        if(sizeof(player_action)==2)
        {
                // all finish,go fire
                if(game_mode==0)
                        before_fire();
                else if(game_mode==1)
                        start_fire();
        }
        return 1;
}

int do_fire(string arg)
{
        int i,x,y;
        mixed *sh,*tb;
        string id;

        if(!is_playing(this_player()))
                return notify_fail("你都不玩啊！\n");
        
        if(game_mode!=1)
                return notify_fail("現在不是布置火力的時候。\n");

        if( !arg || sscanf(arg, "%d %d", x, y)!=2 )
                return notify_fail("place X坐標 Y坐標\n");

        if(x<1||x>WIDTH)
                return notify_fail("X坐標錯誤\n");
        if(y<1||y>HEIGHT)
                return notify_fail("Y坐標錯誤\n");

        id=query("id", this_player());
        sh = get_ship(id);
        tb = get_table(enemy_id(id));
        if(!sh||!tb)
                return notify_fail("access date fail\n");

        if(tb[x-1][y-1][1] != 0)
                return notify_fail("該處已經布置了火力\n");

        for(i=0;i<SHIP_NUM;i++)
        {
                if(!sh[i][0]&&!sh[i][3])
                {
                        sh[i][3] = x;
                        sh[i][4] = y;
                        sh[i][5] = tb[x-1][y-1][1];
                        tb[x-1][y-1][1] = 2;
                        break;
                }
        }

        if(i==SHIP_NUM)
                return notify_fail("你已經沒有空余的火力可以布置了。\n");
        else
        {
                display(player_id(id));
                if(i+1==SHIP_NUM)
                        tell_object(this_player(),"\n使用[Finish]結束布置火力。\n");
        }
        return 1;
}

int do_unfire(string arg)
{
        int i,x,y;
        mixed *sh,*tb;
        string id;

        if(!is_playing(this_player()))
                return notify_fail("你都不玩啊！\n");
        
        if(game_mode!=1)
                return notify_fail("現在不是布置火力的時候。\n");

        if( !arg || sscanf(arg, "%d %d", x, y)!=2 )
                return notify_fail("unplace X坐標 Y坐標\n");

        if(x<1||x>WIDTH)
                return notify_fail("X坐標錯誤\n");
        if(y<1||y>HEIGHT)
                return notify_fail("Y坐標錯誤\n");

        id=query("id", this_player());
        sh = get_ship(id);
        tb = get_table(enemy_id(id));
        if(!sh||!tb)
                return notify_fail("access date fail\n");

        for(i=0;i<SHIP_NUM;i++)
        {
                if(!sh[i][0]&&sh[i][3]==x&&sh[i][4]==y)
                {
                        sh[i][3] = 0;
                        sh[i][4] = 0;
                        tb[x-1][y-1][1] = sh[i][5];
                        display(player_id(id));
                        break;
                }
        }

        if(i==SHIP_NUM)
                return notify_fail("該位置沒有布置火力。\n");
        return 1;
}

int which_ship(mixed* sh,int x,int y)
{
        int i;
        for(i=0;i<SHIP_NUM;i++)
        {
                if(sh[i][1]==x&&sh[i][2]==y)
                        return i;
        }
        return -1;
}

int fire_it()
{
        int i,j1,j2,x,y,bFire;
        int r1,r2;
        string key1,key2;
        string m;
        mixed *sh1,*sh2;
        mixed *tb1,*tb2;
        
        key1 = keys(player)[0];
        key2 = keys(player)[1];
        sh1 = get_ship(key1);
        sh2 = get_ship(key2);
        tb1 = get_table(key1);
        tb2 = get_table(key2);

        game_mode = 2;

        m = 0;
        bFire = 0;

        fire_x = ({0,0});
        fire_y = ({0,0});

        if(sh1&&sh2)
        {
                for(i=0;i<SHIP_NUM;i++)
                {
                        j1 = -1;
                        j2 = -1;
                        if(!sh1[i][0]&&sh1[i][3])
                        {
                                // fire it
                                x = sh1[i][3];
                                y = sh1[i][4];
                                fire_x[0] = x;
                                fire_y[0] = y;
                                sh1[i][3] = 0;
                                sh1[i][4] = 0;
                                tb2[x-1][y-1][1] = 1;
                                j2 = which_ship(sh2,x,y);
                                bFire = 1;
                        }

                        if(!sh2[i][0]&&sh2[i][3])
                        {
                                // fire it
                                x = sh2[i][3];
                                y = sh2[i][4];
                                fire_x[1] = x;
                                fire_y[1] = y;
                                sh2[i][3] = 0;
                                sh2[i][4] = 0;
                                tb1[x-1][y-1][1] = 1;
                                j1 = which_ship(sh1,x,y);
                                bFire = 1;
                        }

                        if(j1>=0)
                        {
                                m = BLINK HIY + key1 + "的船被擊沉了。\n" NOR;
                                sh1[j1][0] = 1;        // be fired
                                if(sh1[j1][3])
                                {
                                        x = sh1[j1][3];
                                        y = sh1[j1][4];
                                        sh1[j1][3] = 0;
                                        sh1[j1][4] = 0;
                                        tb2[x-1][y-1][1] = sh1[j1][5];
                                }
                        }
                        if(j2>=0)
                        {
                                if(!m)m="";
                                m = m + BLINK HIY + key2 + "的船被擊沉了。\n" NOR;
                                sh2[j2][0] = 1;        // be fired
                                if(sh2[j2][3])
                                {
                                        x = sh2[j2][3];
                                        y = sh2[j2][4];
                                        sh2[j2][3] = 0;
                                        sh2[j2][4] = 0;
                                        tb1[x-1][y-1][1] = sh2[j2][5];
                                }
                        }

                        if(bFire)break;
                }
        }

        if(bFire)
        {
                msg(0,0,BLINK HIR"\n~~~~~ 攻擊！！ ~~~~~\n"NOR);
                if(m)msg(0,0,m);
                display(0);
                remove_call_out("fire_it");
                call_out("fire_it",4);
        }
        else
        {
                // fire finish
                r1 = 0;
                r2 = 0;
                for(i=0;i<SHIP_NUM;i++)
                {
                        if(!sh1[i][0])r1++;
                        if(!sh2[i][0])r2++;
                }

                if(r1==0||r2==0)
                {
                        game_mode = 3;
                        if(r1==0)
                        {
                                if(r2==0)
                                        who_win = -1;
                                else
                                        who_win = 1;
                        }
                        else
                                who_win = 2;

                        display(0);
                        msg(0,0,HIR"\n\n 所有戰鬥結束了，使用(start)重新開始。\n"NOR);
                }
                else
                {
                        msg(0,0,sprintf(HIC"\n該回合攻擊結束...\n%s(%d) VS %s(%d)\n"NOR,key1,remain_ship(key1),key2,remain_ship(key2)));
                        before_fire();
                }
        }
}

int do_visitor(string arg)
{
        string key;
        object me,ob;
        int del;

        if(!arg)
                return notify_fail("visit [-]玩家ID\n");

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
                        return notify_fail("這裡沒有這個玩家啊？\n");

                if(del)
                {
                        if( !is_visitor(ob,query("id", me)) )
                                return notify_fail("不是你的觀戰者了。\n");

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
                                visitor[query("id",me)] += query("id",ob); 
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

int do_rplace(string arg)
{
        int i,x,y;
        mixed *sh,*tb;

        if(!is_playing(this_player()))
                return notify_fail("你都不玩啊！\n");
        
        if(!has_start||game_mode!=0)
                return notify_fail("現在不是布置船只的時候。\n");
        
        sh = get_ship(query("id",this_player())); 
        tb = get_table(query("id",this_player())); 
        for(i=0;i<SHIP_NUM;i++)
        {
                if(!sh||!tb)
                        return notify_fail("access date fail\n");

                if(!sh[i][1])
                {
                        x = random(WIDTH)+1;
                        y = random(HEIGHT)+1;

                        if(tb[x-1][y-1][0] != 1)
                        {
                                sh[i][1] = x;
                                sh[i][2] = y;
                                tb[x-1][y-1][0] = 1;
                        }
                }
        }

        display(player_id(query("id",this_player()))); 
        return 1;
}

int do_help(string arg)
{
        this_player()->start_more( @HELP
海戰棋使用方法:
──[開始遊戲]───────────────
幫助命令：helpboard
加入命令：join　　　　　加入遊戲
開始命令：start 　　　　開始遊戲
重置命令：reset board 　結束遊戲

──[船只布置]───────────────
放置船只：place X坐標 Y坐標
取消放置：unplace X坐標 Y坐標
隨機放置：rplace
放置結束：finish

──[火力布置]───────────────
放置火力：fire X坐標 Y坐標
取消放置：unfire X坐標 Y坐標
放置結束：finish

──[觀戰命令]───────────────
觀戰命令：visit [-d] 玩家ID
                邀請其它玩家觀看你的遊戲。
                加參數 -d 表示刪除該玩家的觀看資格。

──[遊戲規則]───────────────
該遊戲是兩人遊戲。
分為準備和戰鬥階段兩個階段。

在準備階段，各人把自己的船放置于自己的
棋盤上。當各人都準備好以後，進入戰鬥階
段。

在戰鬥階段，各人決定攻擊的位置。每一艘
船有 1次攻擊機會。在完成攻擊設置以後，
進入戰鬥狀態。系統根據雙方的攻擊設置進
行攻擊，當攻擊位置上有敵方船，則可以把
對方該船擊毀。被擊毀的船喪失攻擊能力。

在所有攻擊結束以後，重新進入攻擊設置。
如此循環，直到一方的船全部被擊毀。

遊戲開始時候，每人有10艘船。
最後誰的船最先被全部消滅掉，誰為輸者。

──────────────────────
HELP
        );
        return 1;
}