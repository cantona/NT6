//tangltt.c                四川唐門—老太太卧室

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "卧室");
        set("long",
"這是唐門掌門唐老太太的卧室，很簡單，沒有什麼特別。\n"
);
        set("exits", ([
                        "south" : __DIR__"nzlang3",
        ]));
        set("area", "tangmen");
        set("objects", ([
                CLASS_D("tangmen") + "/tangltt" : 1,
        ]));
        setup();
        replace_program(ROOM);
}