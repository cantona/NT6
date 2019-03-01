// Room: /d/baihuagu/huagu2.c
// Last Modified by Winder on Mar. 5 2001

#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", HIR"百花谷"NOR);
        set("long", 
HIG"來到此處，你突然眼前一亮，但覺青青翠谷，點綴著或紅或紫，
或黃或白的鮮花，竟是換了一個世界。道旁有一株桃樹，開得正艷。\n"NOR);  
        set("outdoors", "baihuagu");
        set("exits", ([
                "out"  :__DIR__"huagu1",
                "east" :__DIR__"huagu3",
                "north":__DIR__"huagu2",
                "west" :__DIR__"huagu2",
                "south":__DIR__"huagu2",
                "enter":__DIR__"huagu2",
        ]));
        set("objects", ([
        ]));
        set("no_clean_up", 0);
        set("coor/x", -450);
        set("coor/y", -360);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}