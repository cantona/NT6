#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short",HIB"藍隊西路"NOR);
        set("long",@LONG
搶旗戰場

敘述征求，一格 2 玄黃
LONG);
        set("flag_war", 1);
        set("no_magic", 1);
        
        set("exits",([
         "northwest":__DIR__"bnw4",
         "southeast":__DIR__"bnw2",
        ]));        
        setup();
}