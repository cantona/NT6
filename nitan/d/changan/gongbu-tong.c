//Room: gongbu-tong.c

#include <ansi.h>
#include <room.h>

inherit PRODUCING_ROOM;

void create ()
{
        set ("short", "工部銅廠");
        set("long", @LONG
這是工部的冶銅場地，專門揀選來自全國各地運來的銅礦石，然
後溶化冶煉精銅，最後鑄成銅錠發到全國各地，當然一個主要用途是
用來鑄造國家發行的貨幣。
LONG );
        set("exits",  ([ //sizeof() == 2
                "south" : __DIR__"gongbu",
        ]));

        set("objects", ([
                __DIR__"npc/worker-liu" : 1,
        ]));

        set("no_fight", 1);
        set("no_sleep_room", 1);

        set("product/cuprum", ([ "name" : "黃銅",
                                 "rate" : 100,
                                 "max"  : 10000,
                                 "cost" : ({ "cuprum_ore" }), ]));

        set("product/cuprum_ore", ([ "name" : "銅礦石",
                                     "max"  : 10000,
                                     "rate" : 50, ]));

        set("coor/x", -10710);
	set("coor/y", 1910);
	set("coor/z", 0);
	setup();

        set_heart_beat(120);
        replace_program(PRODUCING_ROOM);
}