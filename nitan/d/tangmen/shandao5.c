//shandao5.c                四川唐門—後山山道

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "山道");
        set("long",
"這裏是通向山頂的小道。奇陡無比，一不小心就會摔下去，兩邊是高\n"
"聳入雲的參天大樹，越接近山頂温度越低了，你扣緊衣襟仍感到寒氣逼人，\n"
"再向上就是裂星崖了。\n"
);
        set("exits", ([
                "southdown" : __DIR__"shandao4",
                "northup" : __DIR__"liexingya",
        ]));
        set("area", "tangmen");
        set("objects", ([
                __DIR__"npc/duwang" : 1,
                __DIR__"npc/wolf" : 1,
        ]));
        set("outdoors", "tangmen");
        setup();
        replace_program(ROOM);
}