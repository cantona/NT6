//Room: /d/dali/feilihusouth.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","妃麗湖南岸");
        set("long",@LONG
這裏是休獵部的漁船碼頭。岸邊有台夷村民正在扎制竹筏，一些
漁民划着竹筏下湖捕魚，新鮮的魚鼈可以在附近的喜州、龍口等城鎮
賣出好價錢。
LONG);
        set("objects", ([
           __DIR__"npc/yufu": 1,
        ]));
        set("outdoors", "dalis");
        set("exits",([ /* sizeof() == 1 */
            "south"      : __DIR__"hexi",
                "west"     : __DIR__"huanggs",
        ]));
	set("coor/x", -19130);
	set("coor/y", -6970);
	set("coor/z", 0);
	setup();
}

void init()
{
        object me = this_player();
        if( query_temp("xuncheng", me) )
        {
                set_temp("dali_xc/flh", 1, me);
        }
}