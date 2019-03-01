// Room: /d/kunlun/kekexili.c
// Last Modified by winder on Nov. 14 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "可可西裡山");
        set("long",@long
可可西裡山又稱可可稀立山，蒙古語為“青山”的意思。西起木孜
塔格峰，東接巴顏喀拉山，山勢平緩，凍土廣布，高處少永久性積雪與
冰川。除北側有淡水湖欽馬湖外，其余南北星羅棋布的湖泊均為咸水湖。
草木稀疏，人煙極少。
long);
        set("exits",([
                "east"      : __DIR__"bayankala",
                "northwest" : __DIR__"shankou",
                "north"     : __DIR__"xuedi",
        ]));
        set("objects",([
//                "/d/mingjiao/npc/yinli" : 1,
        ]));
        set("outdoors", "kunlun");
        set("coor/x", -100000);
        set("coor/y", 20000);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);    
}