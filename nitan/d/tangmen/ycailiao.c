//ycailiao.c                四川唐門─儲料房

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "儲料房");
        set("long",
"這裡是唐門儲存制造藥物材料的房間。唐門暗器天下無雙，除了暗器\n"
"手法之外，這裡配制各種藥物的材料，是功不可沒。從這裡取走的，是普\n"
"通的藥物材料，當這些材料走出唐門的時候，都會令人心驚膽寒。東北邊\n"
"是一條青石小路。\n"
);
        set("exits", ([
                        "northeast" : __DIR__"houroad2",
        ]));
        set("objects", ([
                __DIR__"npc/yjiading" : 1,
        ]));
        set("area", "tangmen");
        setup();
        replace_program(ROOM);
}