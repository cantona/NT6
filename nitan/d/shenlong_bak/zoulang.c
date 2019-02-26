// /d/shenlong/zoulang.c 走廊
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
這是一條石走廊，南面通向大廳，北面是練武場，兩邊是用石柱撐
的涼棚，掛滿樹葉、青藤，邊上有許多小石凳可供人休息。一些凳子上
面三三兩兩地坐了許多神龍教的弟子，正在七嘴八舌地談論着什麼。
LONG
        );
        set("outdoors", "shenlong");
        set("exits", ([
                "south": __DIR__"dating",
                "north": __DIR__"wuchang",
        ]));

        set("objects", ([
                __DIR__"npc/mujianping" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
