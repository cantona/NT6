// Room: /d/taiwan/pingye.c
// Last Modifyed by Ahda on Jan. 4 2002

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "平野");
        set("long", @LONG
顏思齊于苯港登陸後，在笨港東南岸的平野，思齊規劃建築了井字
型營寨，中間為大高台，使之成為組織指揮墾荒的中樞。與此同時，派
楊天生率船隊赴漳、泉故裡招募移民，前後計三千余眾。顏思齊將墾民
分成十寨，發給銀兩和耕牛、農具等，開始了台灣最早的大規模拓墾活
動。
LONG );
        set("exits", ([
                "northwest" : __DIR__"taiwanfu",
                "southeast" : __DIR__"zhuluo",
        ]));
        set("objects", ([
                __DIR__"npc/nongfu": 3,
        ]));
        set("outdoors", "taiwan");
        set("coor/x", 2510);
        set("coor/y", -7020);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
