// /d/shenlong/changlang.c 長廊
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "長廊");
        set("long", @LONG
這是一條長廊，西面通向大廳，東面是峯頂，周圍掛滿了樹葉、青
藤，邊上有許多小石凳可供人休息。一些凳子上面三三兩兩地坐了許多
神龍教的弟子，正在七嘴八舌地談論着什麼。
LONG
        );
        set("outdoors", "shenlong");
        set("exits", ([
                "east": __DIR__"tingkou",
                "west": __DIR__"fengding",
        ]));

        set("objects", ([
                __DIR__"npc/fangyi" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
