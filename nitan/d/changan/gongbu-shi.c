//Room: gongbu-tong.c

#include <ansi.h>
#include <room.h>

inherit PRODUCING_ROOM;

void create ()
{
        set ("short", "工部石廠");
        set("long", @LONG
這是工部的收集石料，選料打磨的地方。揀選來自全國各地運來
的石料，分門別類，供京城建築使用。
LONG );
        set("exits",  ([ //sizeof() == 2
                "north" : __DIR__"gongbu",
        ]));

        set("objects", ([
                __DIR__"npc/worker-wang" : 1,
        ]));

        set("no_fight", 1);
        set("no_sleep_room", 1);

        set("product/perfect-stone", ([ "name" : "精石",
                                        "rate" : 300,
                                        "max"  : 50000,
                                        "cost" : ({ "stone" }), ]));

        set("product/stone", ([ "name" : "石料",
                                     "max"  : 50000,
                                     "rate" : 100, ]));

        set("coor/x", -10710);
	set("coor/y", 1890);
	set("coor/z", 0);
	setup();

        set_heart_beat(120);
        replace_program(PRODUCING_ROOM);
}