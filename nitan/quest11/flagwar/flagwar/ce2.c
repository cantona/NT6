#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short",CYN"中區東路"NOR);
        set("long",@LONG
搶旗戰場

敍述徵求，一格 2 玄黃
LONG);
        set("flag_war", 1);
        set("no_magic", 1);
        
        set("exits",([
         "east":__DIR__"ce3",
         "west":__DIR__"ce1",
        ]));        
        setup();
}