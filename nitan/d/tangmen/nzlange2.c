//nzlange2.c                四川唐門—青石小路

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "青石小路");
        set("long",
"這是一條青石鋪就的小路。由於來來往往的人數太多，粗糙的青石已\n"
"經被磨的光滑如鏡。一些唐門的弟子往來穿梭，這裏還真是很熱鬧。\n"
);
        set("exits", ([
                "north" : __DIR__"bingqifang",
                "south" : __DIR__"fangjvfang",
                "east"  : __DIR__"nzlange3",
                "west"  : __DIR__"nzlange1",
        ]));
        set("objects", ([
                CLASS_D("tangmen") + "/tangjue" : 1,
        ]));
        set("area", "tangmen");
        set("outdoors", "tangmen");
        setup();
        replace_program(ROOM);
}