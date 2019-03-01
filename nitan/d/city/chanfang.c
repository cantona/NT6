// Room: chanfang.c
#include <ansi.h>  
inherit ROOM;

void create()
{
        set("short",HIW"揚州產房"NOR);
        set("long", @LONG
這是一間專門為孕婦準備的產房，你的妻子要生Baby就趕快來喲。
LONG );
        set("no_fight",1);
        set("no_sleep_room",1);
        set("no_steal",1);
        set("no_beg",1);
        set("no_study",1);
        set("no_yun",1);

        set("exits", ([
           "down":  __DIR__"yaopu"
        ]));

	set("coor/x", 20);
	set("coor/y", 10);
	set("coor/z", 10);
	setup();
}