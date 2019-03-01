// senlin.c
#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        int a1,a2,a3,a4;
        a1 = 1+random(4);
        a2 = 1+random(4);
        a3 = 1+random(4);
        if (a1 != 1 && a2!=1 && a3!=1) a4=1;
        else a4 = 1+random(4);
       set("short","針葉林");
       set("long", @LONG
這是極西天山腳下的一片針葉林，林中鳥獸成群，滿地舖蓋著厚厚一
層鬆針。西北方的一座高聳的山脈便是天山了，山上終年積雪，山下卻是
綠樹成蔭。往東南走便是大草原，有辛勤的哈薩克族人在那裡放牧。你走
著走著，竟然迷失了道路。
LONG);
        set("exits", ([
             "east"  : __DIR__"senlin"+a1,
             "west"  : __DIR__"senlin"+a2,
             "south" : __DIR__"senlin"+a3,
             "north" : __DIR__"senlin"+a4,        
        ]));
        
        set("objects", ([
                         __DIR__"npc/toulang" : 1,
        ]));

        set("outdoors", "hasake");
        setup();
           
}