#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short",HIR"紅隊東路"NOR);
        set("long",@LONG
搶旗戰場

敍述徵求，一格 2 玄黃
LONG);
        set("flag_war", 1);
        set("no_magic", 1);
        
        set("exits",([
         "southeast":__DIR__"east_flag",
         "northwest":__DIR__"rse4",
        ]));        
        setup();
}