// Room: /yangzhou/pingtai4.c
// Last Modified by Winder on Jul. 20 2000
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "平台");
        set("long", @LONG
這是法性寺山門門前平台，平台設甬道通湖岸道路。平台兩端栽檜
柏、梧桐。北通蓮花橋，西南方就是蓮性寺的山門了。
LONG );
        set("outdoors", "shouxihu");
        set("exits", ([
                "north"     : __DIR__"lianhuaqiao",
                "southwest" : __DIR__"lianxingsi",
        ]));
        set("objects", ([
                "/d/city/npc/liumang" : 2,
        ]));
        set("coor/x", -10);
        set("coor/y", 90);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}