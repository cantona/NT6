//houyuan.c                四川唐門—後院

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "後院");
        set("long",
"這裏是蓮雲閣後院。這風清景幽的園子裏裏面有一池荷塘，靖蜒點水\n"
"、粉蝶翻稱，陽光泛花，墜珊珊，綠芽似舊，拂窗有寒。荷塘寂寂，荷葉\n"
"一搖就像在那兒一片一片的分割光影。這裏通向唐門的鏢房和毒房。\n"
);
        set("exits", ([
                "east" : __DIR__"houroad4",
                "north" : __DIR__"mishi",
        ]));
        set("objects", ([
                 CLASS_D("tangmen") + "/tangao" : 1,
        ]));
        set("area", "tangmen");
        setup();
        replace_program(ROOM);
}