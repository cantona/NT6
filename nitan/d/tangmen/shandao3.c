//shandao3.c                四川唐門─後山山道

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "山道");
        set("long",
"這裡是通向山頂的小道。奇陡無比，一不小心就會摔下去，兩邊是高\n"
"聳入雲的參天大樹，越接近山頂溫度越低了，你扣緊衣襟仍感到寒氣逼人。\n"
);
        set("exits", ([
                "northeast" : __DIR__"shandao4",
                "westdown" : __DIR__"shandao2",
                "southdown" : __DIR__"shanshi5",
        ]));
        set("area", "tangmen");
        set("objects", ([
                __DIR__"npc/wugong" : 1,
                __DIR__"npc/fushe" : 1,
        ]));
        set("outdoors", "tangmen");
        setup();
        replace_program(ROOM);
}