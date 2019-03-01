#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short",HIR"紅隊中路"NOR);
        set("long",@LONG
搶旗戰場

敘述征求，一格 2 玄黃
LONG);
        set("flag_war", 1);
        set("no_magic", 1);
        
        set("exits",([
         "north":__DIR__"rc2",
         "south":__DIR__"rc4",
        ]));        
        setup();
}