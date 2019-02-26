// Room: /d/gumu/bianhou.c
// Last Modifyed by Winder on Jan. 14 2002

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIB"匾後"NOR);
        set("long", @LONG
這裏就是古墓中堂匾額之後，黑漆漆的什麼都看不清楚。匾下石室
裏點着燭火，一片暈黃。裏面似乎還有一條通道。
LONG        );
        set("exits",([
                "down"  : __DIR__"zhongting",
                "enter" : __DIR__"mishi1",
        ]));
        set("objects",([
                __DIR__"obj/silverkey" : 1,
        ]));
        set("coor/x", -3200);
        set("coor/y", 10);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}
