// Room: /d/baihuagu/house1.c
// Last Modified by Winder on Mar. 5 2001

inherit ROOM;
#include <ansi.h>
 void create()
{
         set("short", HIY"周伯通居"NOR);
         set("long", 
"這是間很簡陋的屋子，陳設簡單，由此可見老頑童極于玩而不
極于物。屋角邊靠著一張床。\n");
        set("sleep_room", "1");
        set("exits", ([
                "east"  : __DIR__"house2",
                "north" : __DIR__"house3",
        ]));
        set("objects", ([           
        ]));
        set("no_clean_up", 0);
        set("coor/x", -420);
        set("coor/y", -370);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}