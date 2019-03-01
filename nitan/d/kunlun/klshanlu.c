// Room: /d/kunlun/klshanlu.c
// Last Modified by Winder on Nov. 15 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "昆侖山麓");
        set("long",@long
整個昆侖山脈雪山連綿，冰河垂懸。遠望昆侖，有如橫臥雲彩間的
銀色玉龍。每年春天以後，冰雪融化，匯成了一股股清澈溪流，流入長
江，黃河。
long);
        set("exits",([
                "northup" : __DIR__"shanmen",
                "east"    : __DIR__"shankou",
                "southwest" : __DIR__"kunlun1",
//                "west"    : "/d/fairyland/shanlu1",
        ]));
        set("outdoors", "kunlun");
        set("coor/x", -120000);
        set("coor/y", 30000);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}