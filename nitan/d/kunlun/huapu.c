// Room: /d/kunlun/huapu.c
// Last Modified by winder on Nov. 15 2000

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short","花圃");
        set("long", @LONG
這裡是一個小花圃，種滿了各種西域奇花異草，中原難得一見。
LONG
);
        set("exits", ([ 
                "north" : __DIR__"tieqinju",
                "west"  : __DIR__"huayuan",
        ]));
        set("objects", ([
                __DIR__"obj/flower" : 2,
        ]));
        set("outdoors", "kunlun");
        set("coor/x", -119980);
        set("coor/y", 40130);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);

}