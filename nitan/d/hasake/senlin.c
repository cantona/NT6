// senlin.c
#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
       set("short","針葉林");
       set("long", "這是極西天山腳下的一片針葉林，林中鳥獸成群，滿地舖蓋著厚厚一
層鬆針。西北方的一座高聳的山脈便是天山了，山上終年積雪，山下卻是
綠樹成蔭。往東南走便是大草原，有辛勤的哈薩克族人在那裡放牧。\n");

        set("exits", ([
             "south" : __DIR__"senlin1",
             "north" : __DIR__"senlin"+(1+random(4)),               
             "west"  : __DIR__"senlin"+(1+random(4)),               
             "east"  : __DIR__"senlin"+(1+random(4)),               
        ]));
        
        set("objects", ([
                         __DIR__"npc/bird" : 1,
        ]));

        set("outdoors", "hasake");

        setup();
       replace_program(ROOM);
}