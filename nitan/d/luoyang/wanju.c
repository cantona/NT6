inherit ROOM;

void create()
{
        set("short", "玩具店");
        set("long", @LONG
這是一家手藝店，店面不大，但裡面各種各樣的手工制品還真不少呢，
各式各樣的小泥人，五顏六色的布娃娃，還有一些用木材和竹子做成的小
玩藝，引起了來這裡的小孩子們的注意，想不想也買個玩玩。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"miaohui",
                "west" : __DIR__"fengwei",
                "east" : __DIR__"hutong2",
                "north" : __DIR__"roudian",
        ]));
        set("objects", ([
                "/d/beijing/npc/kid1" : 1,
        ]));

	set("coor/x", -6950);
	set("coor/y", 2170);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}