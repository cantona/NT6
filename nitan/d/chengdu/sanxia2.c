#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "巫峽");
        set("long", @LONG
這裏是長江三峽中的巫峽，也是最大最美的一個峽谷，神女峯高
高的聳立在江邊，遠遠看去，由如一為亭亭玉立的少女，兩岸風景美
不勝收。
LONG );
        set("exits", ([
                "east" :  __DIR__"sanxia1",
                "west" : __DIR__"sanxia3",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");
        set("coor/x", -15050);
	set("coor/y", -1830);
	set("coor/z", -40);
	setup();
        replace_program(ROOM);
}