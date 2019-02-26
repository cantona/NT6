// senlin.c
#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
       set("short","針葉林");
       set("long", @LONG
這是極西天山腳下的一片針葉林，林中鳥獸成羣，滿地鋪蓋着厚厚一
層松針。北方的一座高聳的山脈便是天山了，山上終年積雪，山下卻是綠
樹成蔭。往南走便是大草原，有辛勤的哈薩克族人在那裏放牧。你走着走
着，竟然迷失了道路。
LONG);
        set("exits", ([
             "eastup"  : __DIR__"shanqiu",
             "west"  : "/d/xingxiu/shanjiao",
             "south" : __DIR__"senlin"+(1+random(4)),
             "north" : __DIR__"senlin"+(1+random(4)),               
        ]));
        
        set("outdoors", "hasake");
        setup();            
}