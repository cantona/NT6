#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "紫竹林");
        set("long", @LONG
你眼前突然一遍光明，你來到了一座有許多紫竹搭成的花園(yua
n)面前，裏面飄出陣陣花香，四周紫竹環抱，説不出的詩情畫意。隱
約看到裏面種有些花卉。
LONG );
        set("outdoors", "jingzhou");

        set("exits", ([
                "north" : __DIR__"zizhulin",
                "enter" : __DIR__"xiaoyuan",
        ]));
        set("item_desc", ([
                "yuan": HIM "\n這裏看來是一處種花的好地方，可隱約看到裏面"
                        "種有許許多多\n的花卉，由許多的紫竹搭建而成。\n" NOR
        ]) );
        set("coor/x", -7090);
	set("coor/y", -2100);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}