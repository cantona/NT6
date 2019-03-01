#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short",HIC"東區旗點"NOR);
        set("long",@LONG
搶旗戰場

敘述征求，一格 2 玄黃
LONG);
        set("flag_war", 1);
        set("no_magic", 1);
        
        set("exits",([
         "west" :__DIR__"ce5",
         "southwest":__DIR__"bne5",
         "northwest":__DIR__"rse5",
        ]));        
        setup();
}