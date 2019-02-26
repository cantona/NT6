#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short",HIR"紅隊休息室"NOR);
        set("long",@LONG
搶旗戰場

敍述徵求，一格 2 玄黃
LONG);
        set("flag_war", 1);
        set("no_magic", 1);
        
        set("exits",([
         "south":__DIR__"red_entry",
        ]));        
        setup();
}