//tangting.c                四川唐門—唐聽卧室

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "寢室");
        set("long",
"這是一間簡陋的卧室。屋中只有一張硬木牀和一張棗木紅桌。這裏住\n"
"着唐老太太的貼身保鏢唐聽。\n"
);
        set("exits", ([
                        "west" : __DIR__"nzlang3",
        ]));
        set("area", "tangmen");
        set("objects", ([__DIR__"npc/tangting" : 1,]));
        setup();
        replace_program(ROOM);
}