//                標準描述長度示例                                   |
// “小航海時代”遊戲主支持
// by naihe  2003-06-19  於茂名



#include <ansi.h>
inherit ITEM;


#define B1                "燦爛奪目的黃金劍"        // 金劍  - YEL, HIY
#define B2                "裝滿金幣的寶箱"        // 寶箱  - MAG, HIM
#define B3                "鑲嵌鑽石的金皇冠"        // 皇冠  - YEL, HIY
#define B4                "皇后的鑽石項鍊"        // 項鍊  - CYN, HIC
#define B5                "聖潔的銀盃"                // 銀盃  - WHT, HIW
#define B6                "神祕的白金權杖"        // 權杖  - WHT, HIW
#define B7                "驅逐邪靈的聖十字架"        // 聖架  - HIM, HIM
#define B8                "預示未來的琉璃水晶"        // 水晶  - CYN, HIC
#define B9                "鑲嵌紅寶石的力量之戒"        // 寶戒  - RED, HIR
#define B10                "與希望同行的綠翡翠"        // 翡翠  - GRN, HIG


string game_now = "等待移動命令";
string att_now = "not_ok";
int target_hp, target_damage;
string pic_me, pic_target;



void new_game_set( int amount, string mark );
void map();
void check_hp();
object get_me();
string get_msg( int x, int y, string type );
void xunbaotu();
void fight_start( string who );
void be_attack();
void target_check_hp();


int finded_baowu( int which, string name )
{
        object me = get_me();
        int score;

        if( !me ) return 0;

        addn("be_finded", 1);
        set("b"+ which, HIW + query("b"+ which) );
        map();
        write(HIC"〖小航海時代〗  太幸運了！終於找到了 "+ name + " ！\n"NOR);

        if( query("be_finded") == 10 )
        {
                delete_temp("hanghai_gameing", me);
                game_now = "遊戲結束";
                score = query("score");

                score += query("att_hp") * 500;
                score += query("att_jf") * 500;
                score += query("att_rs") * 500;
                score += query("att_yq") * 500;
                score += query("att_fd") * 500;

                score += query("hp") * 1000;

                if( score < 1 ) score = 1;
                addn("combat_exp", 500, me);

                write(HIY"
=========================================
             〖小航海時代〗

    你找齊了十件寶物！！遊戲勝利結束了。
    你的最終得分是 "+score+" 分(僅供參考)。

    你獲得了 500 點 經驗值的獎勵！
=========================================
\n"NOR);

                message_vision("$N成功地完成了 小航海時代 遊戲！\n", me);
                remove_call_out("del_me");
                call_out("del_me", 1);
        }

        return 1;
}


// 獲得“me”
object get_me()
{
        object me;
        if( !query("owner_id") ) return 0;

        me = find_player( query("owner_id") );
        if( !me ) return 0;
        return me;
}

// 獲得攻擊力段
int damage( int type )  // 6-11
{
        if( !type || type<1 || type>5 ) type = 1;

        switch( type )
        {
                case 1:        return ( 6+random(6) );
                case 2:        return ( 12+random(6) );
                case 3:        return ( 18+random(6) );
                case 4:        return ( 24+random(6) );
                case 5:        return ( 30+random(6) );
        }

        return (6+random(6));
}

void del_me()
{
        destruct( this_object() );
}

void create()
{
        set_name(HIY"經緯儀（遊戲道具）"NOR, ({"jingwei yi","yi"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", "〖小航海時代〗遊戲的主要道具，有了它才可以進行遊戲。

查詢現在的遊戲狀態，輸入： game check
任何時候結束遊戲，輸入：   game over
\n");
                set("unit", "具");
                set("value", 0);
        }

        set("no_get", 1);
        set("no_drop",1);
        set("no_steal",1);
        set("no_give",1);
        setup();
}


void init()
{
        add_action("do_game", "game");
        add_action("do_go", "go");
        add_action("do_liaowang", "liaowang");
        add_action("do_attack", "atk");
}


void new_game(object me)
{
        if( !me ) return del_me();

        set("owner_id", getuid(me));
        set("owner_name",query("name", me));

// ******************************************
        new_game_set( 8, "島嶼" );

// ******************************************
        new_game_set( 4, "望遠鏡" );

// ******************************************
        new_game_set( 4, "報警探索儀" );

// ******************************************
        new_game_set( 4, "尋寶圖" );

// ******************************************
//        new_game_set( 2, "旋渦" );
// 不要旋渦的設置！

// ******************************************
        new_game_set( 2, "冰山" );

// ******************************************
        new_game_set( 3, "補給品" );

// ******************************************
        new_game_set( 6, "海盜船" );

// ******************************************
        new_game_set( 6, "巨型章魚" );

// ******************************************
        new_game_set( 6, "海藤精怪" );

// ******************************************
        new_game_set( 6, "火神鳥" );

// ******************************************
        new_game_set( 6, "幽靈船" );


// 寶物部分
// ******************************************
        new_game_set( 1, B1);
        new_game_set( 1, B2);
        new_game_set( 1, B3);
        new_game_set( 1, B4);
        new_game_set( 1, B5);
        new_game_set( 1, B6);
        new_game_set( 1, B7);
        new_game_set( 1, B8);
        new_game_set( 1, B9);
        new_game_set( 1, B10);

        new_game_set( 1, "當前船隻位置");

        set("att_rb", 999999);
        set("att_hp", 1);
        set("att_jf", 1);
        set("att_rs", 1);
        set("att_yq", 1);
        set("att_fd", 1);
        set("hp", 100);

        write(">>>>>>>  各類武器及船隻補給完畢。\n");
        set_temp("hanghai_gameing", "waiting_go", me);
        write("\n============ 設置成功！正在進入遊戲…… ============\n");


        set("b1", YEL"金劍"NOR);
        set("b2", YEL"寶箱"NOR);
        set("b3", YEL"皇冠"NOR);
        set("b4", CYN"項鍊"NOR);
        set("b5", WHT"銀盃"NOR);
        set("b6", WHT"權杖"NOR);
        set("b7", RED"聖架"NOR);
        set("b8", CYN"水晶"NOR);
        set("b9", RED"寶戒"NOR);
        set("b10",GRN"翡翠"NOR);

        call_out("game_start", 1);
}

void new_game_set( int amount, string mark )
{
        int x, y;
// 這裏的 x, y ， x是豎數第幾橫，y是橫數第幾個。

        while( amount-- )
        {
                x = 1 + random(10);
                y = 1 + random(16);

                if( query( "aaa(" +x+ "," +y+ ")" ) )
                {
                        amount ++;
                        continue;
                }

                set( "aaa(" +x+ "," +y+ ")" , mark );
                if( mark == "當前船隻位置" )
                {
                        set("now_x", x);
                        set("now_y", y);
                }
                if( mark == "島嶼" )
                        set("island("+x+","+y+")", "new" );

        }
        write( ">>>>>>>  " + mark + " 設置完畢。\n");
}

void game_start()
{
        object me = get_me();
        if( !me ) return del_me();

        set_temp("hanghai_gameing", "ok", me);
        message_vision("$N進入了 小航海時代 遊戲！\n", me);

        write("\n**************************************
進入遊戲成功！遊戲目標為尋得10件寶物！
移動指令與 MUD 內相同。祝遊戲愉快！
**************************************\n\n");

        map();
}


////////////////////////////////////
/////////  玩家操作函數  ///////////
////////////////////////////////////

int do_game(string arg)
{
        object me = this_player(), who;
        who = get_me();

        if( !who || me != who ) return 0;

        if( !arg || ( arg!= "check" && arg != "ck" && arg != "over") )
                return 0;

        if( !query_temp("hanghai_gameing", me) )
                return 0;

        if( arg == "check" || arg == "ck" )
        {
                map();
                return 1;
        }

        if( arg == "over" )
        {
           if( query_temp("hanghai_gameing", me) == "waiting_go" )
                   return 0;

                delete_temp("hanghai_gameing", me);
                message_vision("$N中途放棄，退出了 小航海時代 遊戲。\n", me);
                write(HIR"\n  #########  已退出遊戲，祝一切愉快！ #########\n\n"NOR);
                remove_call_out("del_me");
                call_out("del_me", 1);
                return 1;
        }
        return 1;
}

int do_go(string arg)
{
        object me = this_player(), who;
        int x, y, old_x, old_y, i;

        array dirs = ({
"north", "south", "west", "east", "northwest", "northeast", "southwest", "southeast", });

        string here, msg;

        who = get_me();
        if( !who || who != me ) return 0;
        if( member_array( arg , dirs ) == -1 ) return 0;

        if( query_temp("hanghai_gameing", me) != "ok" )
                return notify_fail("現在不許移動！正在： "+ game_now + " 。\n");

        x = query("now_x");
        y = query("now_y");

        old_x = x;
        old_y = y;

        switch( arg )
        {
                case "north": x--; break;
                case "south": x++; break;
                case "west" : y--; break;
                case "east" : y++; break;
                case "northwest" : x--; y--; break;
                case "northeast" : x--; y++; break;
                case "southwest" : x++; y--; break;
                case "southeast" : x++; y++; break;
        }

        if( x<1 || y<1 || x>10 || y>16 )
                return notify_fail("這個方向已經無法前進了！\n");

        set("be_finded(" +old_x+ "," +old_y+ ")", 1); 


        if( query( "island(" +old_x+ "," +old_y+ ")" ) == "new"
        || query( "island(" +old_x+ "," +old_y+ ")" ) == "old" )
        {
                set("island(" +old_x+ "," +old_y+ ")", "old");
                set("aaa("+old_x+","+old_y+")", "舊的島嶼");
        }

        if( !query( "island(" +old_x+ "," +old_y+ ")" ) )
                delete("aaa(" +old_x+ "," +old_y+ ")" );

        here = query( "aaa(" +x+ "," +y+ ")" );

        set("aaa(" +x+ "," +y+ ")", "當前船隻位置");
        set("now_x", x);
        set("now_y", y);

// 各類判斷！！！

        if( here == "島嶼" )
        {
                addn("att_hp", 1);
                addn("att_jf", 1);
                addn("att_rs", 1);
                addn("att_yq", 1);
                addn("att_fd", 1);
                addn("hp", 20+random(11));
                if( query("hp") > 100 ) set("hp", 100);
                map();
                write(HIG"〖小航海時代〗  發現島嶼！得到了彈藥補給和船隻修理。\n"NOR);
                return 1;
        }

        if( here == "補給品" )
        {
                addn("hp", 20+random(11));
                if( query("hp") > 100 ) set("hp", 100);
                map();
                write(HIC"〖小航海時代〗  發現修補材料！船隻得到了修理。\n"NOR);
                return 1;
        }

        if( here == "冰山" )
        {
                addn("hp", - (30+random(11)));
                map();
                write(HIR"〖小航海時代〗  糟糕！撞上了冰山！船受到了嚴重的損壞。\n"NOR);
                check_hp();
                return 1;
        }

        if( here == B1 )
                return finded_baowu( 1, B1 );
        if( here == B2 )
                return finded_baowu( 2, B2 );
        if( here == B3 )
                return finded_baowu( 3, B3 );
        if( here == B4 )
                return finded_baowu( 4, B4 );
        if( here == B5 )
                return finded_baowu( 5, B5 );
        if( here == B6 )
                return finded_baowu( 6, B6 );
        if( here == B7 )
                return finded_baowu( 7, B7 );
        if( here == B8 )
                return finded_baowu( 8, B8 );
        if( here == B9 )
                return finded_baowu( 9, B9 );
        if( here == B10 )
                return finded_baowu( 10, B10 );


        if( here == "望遠鏡" )
        {
                game_now = "瞭望中 （指令： liaowang x y）";
                map();
                write(HIM"〖小航海時代〗  發現瞭望遠鏡！輸入 (liaowang x y) 指令查看該點周邊海域的情形！ \n"NOR);
                set_temp("hanghai_gameing", "wangyuanjing", me);
                return 1;
        }

        if( here == "報警探索儀" )
        {
                map();
                write(HIM"〖小航海時代〗  發現了報警探索儀！\n"NOR);


                msg = HIM"\n報警儀探索中……自動探索 "+x+","+y+" 區域的情況。\n\n";

                msg += get_msg( x-1,y-1, "bjy" );
                msg += get_msg( x-1,y,   "bjy" );
                msg += get_msg( x-1,y+1, "bjy" );
                msg += get_msg( x,  y-1, "bjy" );
                msg +=         get_msg( x,  y,   "bjy" );
                msg +=         get_msg( x,  y+1, "bjy" );
                msg +=         get_msg( x+1,y-1, "bjy" );
                msg +=         get_msg( x+1,y,   "bjy" );
                msg +=         get_msg( x+1,y+1, "bjy" );

                msg += "\n探索危險區域報警完畢。\n\n"NOR;
                write( msg );
                return 1;
        }

        if( here == "尋寶圖" )
        {
                map();
                write(HIC"〖小航海時代〗  發現了尋寶圖！\n"NOR);
                xunbaotu();
                return 1;
        }


        if( here == "海盜船" || here == "火神鳥" || here == "海藤精怪"
         || here == "巨型章魚" || here == "幽靈船" )
        {
                game_now = "與 "+ here+ " 戰鬥中！ 等待敵人攻擊";
                set_temp("hanghai_gameing", "fighting", me);
                att_now = "not_ok";
                map();
                write(HIR"〖小航海時代〗  糟糕！遭遇了 "+ here+ " ！進入緊急戰鬥狀態！！！\n"NOR);
                set("who_name", here);
                remove_call_out("fight_start");
                call_out("fight_start", 1, here);
                return 1;
        }


        map();
        write(HIW"〖小航海時代〗  漫漫航程，什麼也沒有發現……\n"NOR);
        return 1;
}

void map()
{
        string the_map = HIC"〖小航海時代〗  -- "HIR"HP："+query("hp")+"  寶物："+ query("be_finded")+NOR"\n\n        ", temp_map, temp2;
        int x, y, temp = 0;

        for( x=1; x<11; x++ )
        {
                for( y=1; y<17; y++ )
                {
                        if( temp == 16 )
                        {
                                temp = 0;
                                the_map += "\n        ";
                        }

                        temp2 = "("+x+","+y+")";

                        if( query( "be_finded"+temp2) )
                                temp_map = HIC"□"NOR;
                        else if( query("weixian"+temp2) )
                                temp_map = HIR"■"NOR;
                        else temp_map = HIC"■"NOR;
                        if( query( "aaa"+temp2 ) == "島嶼" )
                                temp_map = HIG"▲"NOR;
                        if( query( "aaa"+temp2 ) == "舊的島嶼" )
                                temp_map = HIG"△"NOR;
                        if( query( "aaa"+temp2 ) == "當前船隻位置" )
                                temp_map = BLINK+HIY"≌"NOR;

                        the_map += temp_map;
                        temp++;
                }
        }

        the_map += "\n\n";

//        for( temp = 1;temp<11;temp++)
//        {
//                set("b"+temp, HIW+query("b"+temp) );
//        }

        the_map += sprintf( "          %s  %s  %s  %s  %s
          %s  %s  %s  %s  %s\n\n",
                query("b1"), query("b2"), query("b3"), 
                query("b4"), query("b5"), query("b6"), 
                query("b7"), query("b8"), query("b9"), 
                query("b10") );

        the_map += sprintf(HIW"  肉搏之刃(rb)：∞  火炮(hp)：%d  巨斧(jf)：  %d
  漫天飛刀(fd)：%d   魚槍(yq)：%d  燃燒彈(rs)：%d\n"NOR,
                query("att_hp"), query("att_jf"), 
                query("att_fd"), query("att_yq"), query("att_rs") );




        write( HIY"================================================\n"NOR +the_map +
HIY"================================================\n"NOR"當前位置：("+ query("now_x") + "," + query("now_y") + ")  現在： "+ game_now +" \n");

}

void check_hp()
{
        object me = get_me();
        int x, y, temp = 0;
        string the_map, temp_map, temp2;

        if( !me ) call_out("del_me", 1);

        if( query("hp") > 0 ) return;

        the_map = HIR"\n〖小航海時代〗  -- 失敗結果公佈(共尋得"+query("be_finded")+"件寶物)\n\n        "NOR;

        for( x=1; x<11; x++ )
        {
                for( y=1; y<17; y++ )
                {
                        if( temp == 16 )
                        {
                                temp = 0;
                                the_map += "\n        ";
                        }

                        temp2 = query("aaa("+x+","+y+")");
                        temp_map = HIC"□"NOR;

                        if( temp2 == "海盜船" )
                                temp_map = HIR"盜"NOR;
                        if( temp2 == "巨型章魚" )
                                temp_map = HIR"魚"NOR;
                        if( temp2 == "海藤精怪" )
                                temp_map = HIR"藤"NOR;
                        if( temp2 == "火神鳥" )
                                temp_map = HIR"鳥"NOR;
                        if( temp2 == "幽靈船" )
                                temp_map = HIR"幽"NOR;
                        if( temp2 == "冰山" )
                                temp_map = HIW"冰"NOR;


                        if( temp2 == "島嶼" )
                                temp_map = HIG"▲"NOR;
                        if( temp2 == "舊的島嶼" )
                                temp_map = HIG"△"NOR;
                        if( temp2 == "當前船隻位置" )
                                temp_map = BLINK+HIB"≌"NOR;

                        if( temp2 == B1 || temp2 == B2 || temp2 == B3
                         || temp2 == B4 || temp2 == B5 || temp2 == B6
                         || temp2 == B7 || temp2 == B8 || temp2 == B9 || temp2 == B10 )
                                temp_map = HIY"寶"NOR;

                        if( temp2 == "望遠鏡" )
                                temp_map = HIM"望"NOR;
                        if( temp2 == "報警探索儀" )
                                temp_map = HIM"警"NOR;
                        if( temp2 == "補給品" )
                                temp_map = HIM"補"NOR;
                        if( temp2 == "尋寶圖" )
                                temp_map = HIM"圖"NOR;

                        the_map += temp_map;
                        temp++;
                }
        }

        the_map += "\n\n";

        write( the_map );
        delete_temp("hanghai_gameing", me);
        game_now = "已經滅亡！";


        message_vision("$N遊戲失敗，退出了 小航海時代 遊戲。\n", me);
        remove_call_out("game_over_over");
        call_out("game_over_over", 1);
        return;
}

void game_over_over()
{
        write(HIR"
=========================================
             〖小航海時代〗

      你的船隻損壞得再也無法支持，
          終於沉入了大海之中！
=========================================
\n"NOR);
        remove_call_out("del_me");
        call_out("del_me", 1);
        return;
}

int do_liaowang( string arg )
{
        object me = this_player(), who;
        int x, y;
        string msg;

        who = get_me();
        if( !who || who != me ) return 0;

        if( query_temp("hanghai_gameing", me) != "wangyuanjing" )
                return 0;

        if( !arg || sscanf( arg, "%d %d", x, y ) != 2 )
                return notify_fail("請輸入正確座標！x -> 豎着數第幾橫  y -> 橫着數第幾個\n");
        if( x<1 || x>10 || y<1 || y>16 )
                return notify_fail("請輸入正確座標！x -> 豎着數第幾橫  y -> 橫着數第幾個\n");


        msg = HIM"瞭望中……你決定查看 "+x+","+y+" 區域的情況。\n\n";

        msg += get_msg( x-1,y-1, "wyj" );
        msg += get_msg( x-1,y,   "wyj" );
        msg += get_msg( x-1,y+1, "wyj" );
        msg += get_msg( x,  y-1, "wyj" );
        msg +=         get_msg( x,  y,   "wyj" );
        msg +=         get_msg( x,  y+1, "wyj" );
        msg +=         get_msg( x+1,y-1, "wyj" );
        msg +=         get_msg( x+1,y,   "wyj" );
        msg +=         get_msg( x+1,y+1, "wyj" );

        msg += "\n查看完畢。\n\n"NOR;

        write( msg );
        set_temp("hanghai_gameing", "ok", me);
        game_now = "等待移動命令";
        return 1;
}

string get_msg( int x, int y, string type )
{
        string msg;

        if( x<1 || x>10 || y<1 || y>16 ) return "";

        msg = query("aaa(" +x+ "," +y+ ")" );

        if( !msg )
        {
                if( type == "wyj" ) return "("+x+","+y+") -----------\n";
                return "";
        }

        if( msg == "冰山" || msg == "海盜船" || msg == "巨型章魚"
         || msg == "海藤精怪" || msg == "火神鳥" || msg == "幽靈船" )
        {
                set("weixian("+x+","+y+")", 1);
                if( type == "wyj" ) return "("+x+","+y+") " + msg + "\n";
                return "("+x+","+y+") 有危險潛伏！\n";
        }

        if( type == "wyj" ) return "("+x+","+y+") " + msg + "\n";
        else return "";
}

void xunbaotu()
{
        int x, y;
        string msg;

        for( x = 1; x<11; x++ )
        {
                for( y=1;y<17;y++)
                {
                        msg = query("aaa(" +x+ "," +y+ ")" );
                        if( msg == B1 || msg == B2 || msg == B3 || msg == B4
                         || msg == B5 || msg == B6 || msg == B7 || msg == B8
                         || msg == B9 || msg == B10 )
                        {
                                write( HIM"("+x+","+y+")    該處藏有寶藏！\n"NOR);
                                return;
                        }
                }
        }
}

void fight_start( string who )
{
        switch( who )
        {
                case "海盜船": pic_target = "≌";target_damage=2; break;
                case "巨型章魚": pic_target = "∝"; target_damage=4; break;
                case "海藤精怪": pic_target = "※"; target_damage=6; break;
                case "火神鳥": pic_target = "∮"; target_damage=8; break;
                case "幽靈船": pic_target = "≌"; target_damage=10; break;
        }

        target_hp = 50+ random(31);
        pic_me = "≌";

        remove_call_out("be_attack");
        call_out("be_attack", 1);
}

void be_attack()
{
        int damage;
        string pic1, pic2;

        damage = target_damage + random(3);
        addn("hp", -damage);

        pic1 = HIR + pic_target + " " + query("who_name") + "("+ target_hp + ")"NOR;
        pic2 = sprintf("    "HIG"(%|4d)航海者 "HIR"¤"NOR, query("hp"), pic_me);

        write( sprintf("
                     _ _ _ _ _ _ _ _ _ _       ATTACK!
            "HIR"-%-2d"NOR"    /                     `"HIY"¤"NOR"
%s                        %s
≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈\n\n", damage, pic2,  pic1));

        write(HIY"〖小航海時代〗  受到了 "+query("who_name")+ " 的攻擊，船隻損壞 "+ damage +" ！\n"NOR);
        check_hp();
        call_out("can_att", 1);
}

void can_att()
{
        if( query("hp") < 1 ) return;

        write(HIY"〖小航海時代〗  輪到你攻擊了！(atk 方式)\n"NOR);
        write( sprintf(HIG"武器剩餘：    rb:無限    hp:%d    jf:%d    rs:%d    yq:%d    fd:%d\n"NOR,
                query("att_hp"), query("att_jf"), query("att_rs"), query("att_yq"), query("att_fd") ) );
        game_now = "與 "+ query("who_name")+ " 戰鬥中！ 等待攻擊指令";
        att_now = "ok";
}

int do_attack(string arg)
{
        object me = this_player(), who;
        string target_name = query("who_name"), pic1, pic2, temp;
        int damage;

        who = get_me();
        if( !who || who!=me ) return 0;

        if( att_now != "ok" ) return notify_fail("現在並不是你攻擊的時候！\n");
        if( !arg || ( arg != "rb" && arg != "hp" && arg != "jf" && arg != "rs"
         && arg != "yq" && arg != "fd" ) )
                return notify_fail("你選擇的武器不對！\n");

        if( query("att_"+ arg ) < 1 ) return notify_fail("這種武器已經沒有了！\n");
        addn( "att_"+ arg , -1 );

        switch( arg )
        {
                case "rb":  temp = "肉搏之刃"; damage = damage(1); break;
                case "hp":
                        temp = "火炮";
                        if( target_name == "海盜船" ) damage = damage(5);
                        if( target_name == "巨型章魚" ) damage = damage(4);
                        if( target_name == "海藤精怪" ) damage = damage(3);
                        if( target_name == "火神鳥" ) damage = damage(2);
                        if( target_name == "幽靈船" ) damage = damage(1);
                        break;
                case "jf":
                        temp = "巨斧";
                        if( target_name == "海盜船" ) damage = damage(4);
                        if( target_name == "巨型章魚" ) damage = damage(1);
                        if( target_name == "海藤精怪" ) damage = damage(5);
                        if( target_name == "火神鳥" ) damage = damage(3);
                        if( target_name == "幽靈船" ) damage = damage(2);
                        break;
                case "rs":
                        temp = "燃燒彈";
                        if( target_name == "海盜船" ) damage = damage(2);
                        if( target_name == "巨型章魚" ) damage = damage(3);
                        if( target_name == "海藤精怪" ) damage = damage(4);
                        if( target_name == "火神鳥" ) damage = damage(1);
                        if( target_name == "幽靈船" ) damage = damage(5);
                        break;
                case "yq":
                        temp = "魚槍";
                        if( target_name == "海盜船" ) damage = damage(1);
                        if( target_name == "巨型章魚" ) damage = damage(5);
                        if( target_name == "海藤精怪" ) damage = damage(2);
                        if( target_name == "火神鳥" ) damage = damage(4);
                        if( target_name == "幽靈船" ) damage = damage(3);
                        break;
                case "fd":
                        temp = "漫天飛刀";
                        if( target_name == "海盜船" ) damage = damage(3);
                        if( target_name == "巨型章魚" ) damage = damage(2);
                        if( target_name == "海藤精怪" ) damage = damage(1);
                        if( target_name == "火神鳥" ) damage = damage(5);
                        if( target_name == "幽靈船" ) damage = damage(4);
                        break;
        }

        target_hp -= damage;
        addn("score", damage);

        pic1 = HIR"¤" + " " + query("who_name") + "("+ target_hp + ")"NOR;
        pic2 = sprintf("    "HIG"(%|4d)航海者 %s"NOR, query("hp"), pic_me);


        write( sprintf("
       %|8s！    _ _ _ _ _ _ _ _ _ _
                   "HIY"¤"NOR"                     \\    "HIR"-%d"NOR"
%s                        %s
≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈\n\n", temp,damage, pic2,  pic1));

        write(HIY"〖小航海時代〗  使用 "+ temp+ " 對 "+query("who_name")+ " 進行攻擊！損害對方  "+ damage +" 。\n"NOR);

        att_now = "not_ok";
        remove_call_out("target_check_hp");
        call_out("target_check_hp", 1);

        return 1;
}

void target_check_hp()
{
        object me = get_me();
        if( !me )
        {
                remove_call_out("del_me");
                call_out("del_me", 1);
                return;
        }

        if( target_hp < 1 )
        {
                game_now = "等待移動命令";
                addn("hp", 1+(random(5)) );
                if( query("hp") > 100 ) set("hp", 100);
                map();
                write(HIG"\n〖小航海時代〗  打敗了 "+query("who_name")+ " ！獲得了少量的補給。繼續出發吧！\n\n"NOR);
                set_temp("hanghai_gameing", "ok", me);
                addn("score", 100);
                return;
        }

        be_attack();
}
