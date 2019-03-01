//shandao1.c                四川唐門─後山山道

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "山道");
        set("long",
"這裡是通向山頂的小道。奇陡無比，一不小心就會摔下去，兩邊是高\n"
"聳入雲的參天大樹，林中傳來野獸的撕咬聲，令人毛骨悚然、不寒而立，\n"
"你全神貫注生怕有野獸撲來。\n"
);
        set("exits", ([
                        "westdown" : __DIR__"houshan",
                        "northeast" : __DIR__"shandao2",
        ]));
        set("area", "tangmen");
        set("objects", ([
                __DIR__"npc/xiezi" : 1,
                __DIR__"npc/snake" : 1,
        ]));
        set("outdoors", "tangmen");
        setup();
        replace_program(ROOM);
}