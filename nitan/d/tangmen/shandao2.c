//shandao2.c                四川唐門—後山山道

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "山道");
        set("long",
"這裏是通向山頂的小道。奇陡無比，一不小心就會摔下去，兩邊是高\n"
"聳入雲的參天大樹，林中傳來野獸的撕咬聲，令人毛骨悚然、不寒而立，\n"
"你全神貫注生怕有野獸撲來。\n"
);
        set("exits", ([
                "southwest" : __DIR__"shandao1",
                "eastup" : __DIR__"shandao3",
        ]));
        set("area", "tangmen");
        set("objects", ([
                __DIR__"npc/deer" : 1,
                __DIR__"npc/yetu" : 1,
        ]));
        set("outdoors", "tangmen");
        setup();
        replace_program(ROOM);
}