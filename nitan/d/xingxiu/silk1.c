// /d/xingxiu/silk1.c
// Last Modified by winder on Feb. 28 2001

inherit ROOM;

void create()
{
        set("short", "絲綢之路");
        set("long", @LONG
這是一條中原和西域之間的商道。迎面而來的是一個個沙包，星羅
棋佈於荒原之上。一陣風沙吹過，象刀割一樣撕裂着你的臉。東邊有一
座雄偉的關隘，西面則通往西域。
LONG );
        set("outdoors", "silu");
        set("exits", ([
                "east"      : __DIR__"jiayuguan",
                "northwest" : __DIR__"chouchishan",
                "southwest" : __DIR__"xianrenya",
        ]));
        set("objects", ([
                __DIR__"npc/trader" : 1,
        ]));
        set("coor/x", -19000);
        set("coor/y", 400);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}

#include "/d/xingxiu/job2.h";
