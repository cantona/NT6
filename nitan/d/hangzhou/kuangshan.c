// /d/hangzhou/kuangshan.c

#include <ansi.h>
#include <room.h>

inherit PRODUCING_ROOM;

void create()
{
        set("short", "銅礦山");
        set("long", @LONG
這裡是山腳，山坡蜿蜒並不陡峭，很多地方挖開了一些洞口，不
少人出出入入、來來往往，在搬運一些東西。你看到地上有著不少石
頭，藍色晶瑩，好像是寶石一般，似乎質地不是很純，有些地方泛著
白花花的雜質。
LONG );
        set("exits", ([
                "west" : __DIR__"kslu2",
        ]));

        set("objects", ([
                __DIR__"npc/jiangong" : 1,
        ]));

        set("no_fight", 1);

        set("product/cuprum_ore", ([ "name" : "銅礦石",
                                     "rate" : 100,
                                     "max"  : 10000, ]));

        set("outdoors", "hangzhou");
	set("coor/x", 800);
	set("coor/y", -2110);
	set("coor/z", 0);
	setup();
        replace_program(PRODUCING_ROOM);
        set_heart_beat(120);
}