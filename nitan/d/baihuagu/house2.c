// Room: /d/baihuagu/house2.c
// Last Modified by Winder on Mar. 5 2001

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", HIY"周伯通居"NOR);
        set("long", 
"這是間很簡陋的屋子，陳設簡單，由此可見老頑童極于玩而不
極于物。\n");
        set("exits", ([
                "west"  : __DIR__"house1",
                "north" : __DIR__"shanpo1",
        ]));
        set("objects", ([           
        ]));
        set("no_clean_up", 0);
        set("coor/x", -410);
        set("coor/y", -370);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}