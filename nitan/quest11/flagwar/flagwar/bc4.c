#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short",HIB"藍隊中路"NOR);
        set("long",@LONG
搶旗戰場

敍述徵求，一格 2 玄黃
LONG);
        set("flag_war", 1);
        set("no_magic", 1);
        
        set("exits",([
         "north":__DIR__"bc5",
         "south":__DIR__"bc3",
        ]));        
        setup();
}