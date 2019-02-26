// /guanwai/shichang.c

#include <room.h>

inherit PRODUCING_ROOM;

void create()
{
        set("short", "採石場");
        set("long", @LONG
這裏是山腳，眼前驀然聳立着一座大山，不過一側已經被炸得支離
破碎，工人們來來往往，搬運着石料。在北方也有這麼大的石山，你不
禁有些驚訝。眼前有一個人，看起來像個監工。
LONG );
        set("exits", ([
                "west" : __DIR__"tulu",
        ]));

        set("objects", ([
                __DIR__"npc/jiangong" : 1,
        ]));

        set("no_fight", 1);

        set("product/stone", ([ "name" : "石料",
                                "rate" : 1000,
                                "max"  : 200000, ]));

        set("outdoors", "guanwai");
        set("coor/x", 4010);
	set("coor/y", 9220);
	set("coor/z", 0);
	setup();

        set_heart_beat(120);
}