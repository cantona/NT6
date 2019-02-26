// Room: /d/kunlun/kekexili.c
// Last Modified by winder on Nov. 14 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "可可西里山");
        set("long",@long
可可西里山又稱可可稀立山，蒙古語為“青山”的意思。西起木孜
塔格峯，東接巴顏喀拉山，山勢平緩，凍土廣佈，高處少永久性積雪與
冰川。除北側有淡水湖欽馬湖外，其餘南北星羅棋佈的湖泊均為鹹水湖。
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