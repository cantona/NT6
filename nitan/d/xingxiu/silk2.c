// /d/xingxiu/silk2.c
// Last Modified by winder on Feb. 28 2001

inherit ROOM;

void create()
{
        set("short", "絲綢之路");
        set("long", @LONG
這是聞名中外的絲綢古道，一條連接中原和西域之間的商道。南面
連綿的祁連山脈在陽光的照射下好像是一條玉帶。迎面而來的是一個個
沙包，星羅棋布於荒原之上。一陣風沙吹過，象刀割一樣撕裂著你的臉。
東南過仇池山通往嘉峪關，西面穿過頌摩崖，則通往西域。
LONG );
        set("outdoors", "silu");
        set("exits", ([
            "south"     : __DIR__"chouchishan",
            "westup"    : __DIR__"songmoya",
        ]));
        set("objects", ([
                __DIR__"npc/trader" : 1,
        ]));
        set("coor/x", -20000);
        set("coor/y", 600);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}

#include "/d/xingxiu/job2.h";
