#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short",HIR"紅隊西路"NOR);
        set("long",@LONG
搶旗戰場

敍述徵求，一格 2 玄黃
LONG);
        set("flag_war", 1);
        set("no_magic", 1);
        
        set("exits",([
         "southwest":__DIR__"rsw5",
         "northeast":__DIR__"rsw3",
        ]));        
        setup();
}