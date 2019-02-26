//nzlangw3.c                四川唐門—青石小路

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "青石小路");
        set("long",
"這是一條青石鋪就的小路。由於來來往往的人數太多，粗糙的青石已\n"
"經被磨的光滑如鏡。一些唐門的弟子往來穿梭，這裏還真是很熱鬧。這裏向\n"
);
        set("exits", ([
                        "east" : __DIR__"nzlangw2",
                        "west" : __DIR__"shufang",
                        "north" : __DIR__"brestroom",
                        "south" : __DIR__"grestroom",
        ]));
        set("area", "tangmen");
        set("outdoors", "tangmen");
        setup();
//        replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
        if( (dir == "north") && (query("gender", me) != "男性") )
                return notify_fail("喂！那裏都是男人呀！\n");

        if( (dir == "south") && (query("gender", me) != "女性") )
                return notify_fail("喂！擅闖女弟子休息室，犯門規的！\n");

        return ::valid_leave(me, dir);
}