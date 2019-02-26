// Room:  /d/luoyang/baiyuan.c
// Last modified by winder 2002.11.11

#include <ansi.h>;
inherit  ROOM;

void  create  ()
{
        set("short",  "白園");
        set("long",  @LONG
白園或稱白冢，在東香山北端琵琶峯上。墓前石碑刻“唐少傅白公
墓”六字。白居易晚年寓居香山，自號“香山居士”。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "westdown" : __DIR__"longmen",
        ]));
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
	set("coor/x", -6970);
	set("coor/y", 2060);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}