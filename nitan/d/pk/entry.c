// Room: /d/pk/entry.c

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "屠人場入口");
        set("long", @LONG
這裏是一間不算大的小屋，當中擺了一個桌子，後面做着一個人，
正笑吟吟的看着你。他身後有一扇門，虛掩着，裏面黑乎乎的，也不知
道通往哪裏。西面望出去是寬闊敞亮的大街，讓人無限嚮往。
LONG
        );
        set("exits", ([
                "north" : __DIR__"ready",
                "west"  : "/d/changan/yongtai-dadao2",
        ]));

        set("objects", ([
                __DIR__"npc/wu" : 1,
        ]));

        set("no_fight", 1);
        setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "north")
                return notify_fail("烏老大喝道：給我站住！那兒不能隨意進入。\n");

        return ::valid_leave(me, dir);
}