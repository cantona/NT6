//tangwen.c                四川唐門─唐聞臥室

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "寢室");
        set("long",
"這是一間簡陋的臥室。屋中只有一張硬木床和一張棗木紅桌。這裡住\n"
"著唐老太太的貼身保鏢唐聞。\n"
);
        set("exits", ([
                        "east" : __DIR__"nzlang2",
        ]));
        set("area", "tangmen");
        set("objects", ([__DIR__"npc/tangwen" : 1,]));
        setup();
        replace_program(ROOM);
}