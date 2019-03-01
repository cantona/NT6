//nzlange3.c                四川唐門─碎石小路

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "碎石小路");
        set("long",
"這是一條碎石舖就的小路。一些唐門的弟子往來穿梭，這裡還真是很\n"
"熱鬧。這裡向\n"
);
        set("exits", ([
                        "west"  : __DIR__"nzlange2",
                        "east"  : __DIR__"lianparry",
                        "north" : __DIR__"lianthrow",
                        "south" : __DIR__"liandodge",
        ]));
        set("area", "tangmen");
        set("outdoors", "tangmen");
        setup();
//        replace_program(ROOM);
}