#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short",HIC"西區旗點"NOR);
        set("long",@LONG
搶旗戰場

敍述徵求，一格 2 玄黃
LONG);
        set("flag_war", 1);
        set("no_magic", 1);
        
        set("exits",([
         "east" :__DIR__"cw5",
       	 "southeast":__DIR__"bnw5",
       	 "northeast":__DIR__"rsw5",
        ]));        
        setup();
}