//exiaolu1.c                四川唐門─碎石小路

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "碎石小路");
        set("long",
"這裡是後山小路。只容一人通過，兩邊雜草叢生，不時傳出悉悉索索\n"
"的撥草聲，偶爾還有一兩只小動物自面前掠過，小路彎彎曲曲的向前伸去，\n"
"通向更加陰暗的後山。\n"
);
        set("exits", ([
                        "south" : __DIR__"chaifang",
                        "east" : __DIR__"exiaolu2",
        ]));
        set("area", "tangmen");
        set("outdoors", "tangmen");
        setup();
        replace_program(ROOM);
}