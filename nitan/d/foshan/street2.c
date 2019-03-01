inherit ROOM;

void create()
{
        set("short", "西鎮街");
        set("long", @LONG
佛山鎮的街道橫亙東西。北邊不遠處有座破敗的廟宇，南面是一
座宏偉的建築，大門上寫著「英雄會館」四個大字。
LONG );
        set("objects", ([
                "/d/city/npc/liumang": 1,
        ]));
        set("outdoors", "foshan");
        set("exits", ([
                "south" : __DIR__"pm_restroom",
                "west"  : __DIR__"street1",
                "east"  : __DIR__"street3",
        ]));
	set("coor/x", -6580);
	set("coor/y", -9750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}