//bcailiao.c                四川唐門─鏢房

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "儲料房");
        set("long",
"這裡是唐門儲存制造暗器材料的房間。鋼鏢，銀針，飛蝗石，鐵蒺藜\n"
"，三叉棱，鐵丸，飛刀，沒羽箭，龍須釘等等等等，所有可以說得上名的\n"
"暗器和制作材料，都可以在這裡尋到它的蹤影。東北面是一條青石小路。\n"
);
        set("exits", ([
                "northeast" : __DIR__"houroad3",
        ]));
        set("objects", ([
                __DIR__"npc/bjiading" : 1,
        ]));
        set("area", "tangmen");
        setup();
        replace_program(ROOM);
}