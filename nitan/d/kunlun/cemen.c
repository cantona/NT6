// Room: /d/kunlun/cemen.c
// Last Modified by winder on Nov. 15 2000

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "側門");
        set("long", @LONG
繞過三聖堂的後花園，經過一條曲曲折折的花徑，又穿入許多廳堂
之中。但見屋宇連綿，門戶復疊，到了昆侖派的側門。
LONG );
        set("exits", ([
//                "west"  : __DIR__"klshanlu1",
//                "north" : __DIR__"westxiangfang",
                "east"  : __DIR__"huayuan",
        ]));
        set("outdoors", "kunlun");
        set("coor/x", -119991);
        set("coor/y", 40130);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}