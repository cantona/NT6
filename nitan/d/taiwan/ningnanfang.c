// Room: /d/taiwan/ningnanfang.c
// Last Modifyed by Ahda on Jan. 4 2002

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "寧南坊");
        set("long", @LONG
鄭經治台時，在台灣府以赤嵌一帶為中心，將市街劃分為四坊，台
灣歸清後，仍保留鄭氏設置之四坊，寧南坊乃赤嵌城南部一坊。
LONG );
        set("exits", ([
                "north" : __DIR__"chiqian",
                "south": __DIR__"dagougang",
        ]));
        set("objects", ([
                __DIR__"npc/bing": 1,
        ]));
        set("outdoors", "taiwan");
        set("coor/x", 2510);
        set("coor/y", -7060);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
