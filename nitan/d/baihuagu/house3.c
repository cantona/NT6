// Room: /d/baihuagu/house3.c
// Last Modified by Winder on Mar. 5 2001

inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", HIY"周伯通居"NOR);
        set("long", 
"這是間很簡陋的屋子，陳設簡單，由此可見老頑童極於玩而
不極於物。\n");
        set("exits", ([
                "south":  __DIR__"house1",
        ]));
        set("no_fight", 1);
        set("objects", ([           
                __DIR__"npc/zhou":1]));
        set("coor/x", -420);
        set("coor/y", -360);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
