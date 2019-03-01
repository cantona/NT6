// Room: /lingzhou/luorilin2.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "落日林");
        set("long", @LONG
這裡是一片方圓百裡的森林，林中古木參天，樹蔭蔽日，光線黯淡，
落日林的伐木場就在這裡，這裡是樹木大都樹齡百年以上，數人和抱的
大樹比比皆是，一條不寬的土路蜿蜒通向前方。
LONG );
        set("exits", ([
                "north"     : __DIR__"tulu",
                "southwest" : __DIR__"dalu",
        ]));
        set("objects", ([
                "/d/city/obj/shuzhi" : 1,
                "/d/shenlong/npc/dushe" : 1,
        ]));
        set("outdoors", "lingzhou");
        set("coor/x", -6235);
        set("coor/y", 2945);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}