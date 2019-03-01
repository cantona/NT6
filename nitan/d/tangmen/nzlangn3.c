//nzlangn3.c                四川唐門─青石小路

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "青石小路");
        set("long",
"這是一條青石舖就的小路。由于來來往往的人數太多，粗糙的青石已\n"
"經被磨的光滑如鏡。一些唐門的弟子往來穿梭，這裡還真是很熱鬧。這裡\n"
"向東通向練功場，向西就是男女弟子的休息室了。\n"
);
        set("exits", ([
                        "west"  : __DIR__"nzlangw1",
                        "south" : __DIR__"nzlangn2",
                        "east"  : __DIR__"nzlange1",
        ]));
        set("area", "tangmen");
        set("outdoors", "tangmen"); 
        setup();
        replace_program(ROOM);
}
