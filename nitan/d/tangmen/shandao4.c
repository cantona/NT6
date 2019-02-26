//shandao4.c                四川唐門—後山山道

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "山道");
        set("long",
"這裏是通向山頂的小道。奇陡無比，一不小心就會摔下去，兩邊是高\n"
"聳入雲的參天大樹，越接近山頂温度越低了，你扣緊衣襟仍感到寒氣逼人。\n"
);
        set("exits", ([
                        "northup" : __DIR__"shandao5",
                        "southwest" : __DIR__"shandao3",
        ]));
        set("area", "tangmen");
        set("objects", ([__DIR__"npc/qingshe" : 1,__DIR__"npc/jinshe" : 1,]));
        set("outdoors", "tangmen");
        setup();
        replace_program(ROOM);
}