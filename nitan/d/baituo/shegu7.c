// Code of ShenZhou
// shegu.c 蛇谷
// maco 7/15/2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "蛇谷平地");
        set("long", @LONG
這是蛇谷的一處較平坦開闊的地帶，地上滿是矮小無葉的駱駝刺
和碎小的亂石。平緩的地勢從這裡往東邊略為延伸，此外各方向都是
斑駁的林木。
LONG );

        set("exits", ([ 
            "southwest" : __DIR__"shegu8",
            "east" : __DIR__"shegu6",
            "northwest" : __DIR__"shegu20",
        ]));
        
        set("objects", ([
            __DIR__"npc/maque" : 2,
        ]));
        set("resource/grass", 1);
        set("cost", 1);
        set("outdoors","baituo");
        set("shegu", 1);
        set("coor/x", -49990);
        set("coor/y", 20170);
        set("coor/z", 20);
        setup();
}