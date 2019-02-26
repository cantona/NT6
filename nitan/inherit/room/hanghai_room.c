//                標準描述長度示例                                   |
// 仿某遊戲而寫成，名字似乎應該照原作，定為“小航海時代” ：）
// 原作很精簡，確為休閒遊戲之典範！是一款需要安裝的，有簡易圖樣的遊戲。


// 本遊戲由 hanghai_master.c (經緯儀) 支持主要指令。
// by naihe  2003-06-19  於茂名

#include <ansi.h>

inherit ROOM;

#define MST                __DIR__"hanghai_master"                // 經緯儀，遊戲指令主支持


void create()
{
        set("short", HIC"〖小航海時代〗 遊戲室"NOR);
        set("long", "
***********************************************
              〖小航海時代〗

    歡迎來到 小航海時代 遊戲。這裏是一個休閒
小遊戲，您在遊戲獲得樂趣的同時，亦將能夠得到
一定數量的MUD獎勵，以資鼓勵。

    進入遊戲：         game start
    任何時候退出遊戲： game over

    BY 奈何(naihe)    --2003.06.19
***********************************************
\n");
        set("no_fight", "1");
        set("no_steal", "1");
        set("no_sleep_room", "1");
        set("valid_startroom", 1); // 此兩條分別為：非連線房間 及 起始房間
        set( "cost", 0 );

        set("exits", ([
            "out":  "/d/city/advice/advice",
        ]));

        setup();
}

void init()
{
        add_action("do_game", "game");
}

int do_game(string arg)
{
        object me = this_player(), mst_obj;

        if( !arg || arg != "start" )
                return 0;

// "game over" 等操作，由 MST 物件進行。


        if( query_temp("hanghai_gameing", me) )
                return notify_fail("你已身在遊戲中！\n");

        if( file_size( MST + ".c" ) < 1 )
                return notify_fail("本遊戲暫停開放！\n");

        write("\n========= 請稍候，正在執行操作…… ==========\n\n");

        mst_obj = new( MST );

        mst_obj->new_game(me);
        mst_obj->move(me);

        return 1;
}



int valid_leave(object me, string dir)
{
        if( query_temp("hanghai_gameing", me) )
                return notify_fail("你正在遊戲中，不得離開！\n");

        return ::valid_leave(me, dir);
}