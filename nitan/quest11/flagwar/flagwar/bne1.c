#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short",HIB"藍隊東路"NOR);
        set("long",@LONG
搶旗戰場

敘述征求，一格 2 玄黃
LONG);
        set("flag_war", 1);
        set("no_magic", 1);
        
        set("exits",([
         "northeast":__DIR__"bne2",
         "southwest":__DIR__"blue_entry",
        ]));        
        setup();
}