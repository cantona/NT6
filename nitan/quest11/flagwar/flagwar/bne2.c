#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short",HIB"藍隊東路"NOR);
        set("long",@LONG
搶旗戰場

敍述徵求，一格 2 玄黃
LONG);
        set("flag_war", 1);
        set("no_magic", 1);
        
        set("exits",([
         "northeast":__DIR__"bne3",
         "southwest":__DIR__"bne1",
        ]));        
        setup();
}