// Room: /d/taiwan/donganfang.c
// Last Modifyed by Ahda on Jan. 4 2002

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "東安坊");
        set("long", @LONG
鄭經治台時，在台灣府以赤嵌一帶為中心，將市街劃分為四坊，台
灣歸清後，仍保留鄭氏設置之四坊，東安坊乃赤嵌城東部一坊。
LONG );
        set("exits", ([
                "west" : __DIR__"chiqian",
        ]));
        set("objects", ([
                __DIR__"npc/bing": 1,
//                __DIR__"npc/shangren": 1,
//                __DIR__"npc/pingpuren": 1,
        ]));
        set("outdoors", "taiwan");
        set("coor/x", 2520);
        set("coor/y", -7050);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
