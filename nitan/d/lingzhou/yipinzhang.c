// Room: /lingzhou/yipinzhang.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "一品堂帳房");
        set("long", @LONG
這裏是西夏一品堂的帳房，自願加入一品堂的江湖高手，都可以領
到餉銀。一個老先生兩眼一抹黑在此管帳。
LONG );
        set("exits", ([
                "east"  : __DIR__"yipindayuan",
        ]));
        set("objects", ([
                __DIR__"npc/zhangfang" :1,
        ]));
        set("coor/x", -6305);
        set("coor/y", 2955);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}