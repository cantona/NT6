// beijie.c 北街
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "北街");
        set("long", @LONG
北街是漢中鎮最繁華的街道，每逢初一十五，還要在這裡舉行
些廟會之類的聚會。街北面是一家酒樓，樓前掛著一條藍幅，上面
寫了個大大的‘酒’字。西面是一戶人家。幾個小孩在街上笑著鬧
著互相追逐。
LONG
        );
        set("outdoors", "hanzhong");
        set("exits", ([
                "south" : __DIR__"zhongxin",
                "north" : __DIR__"jiulou1",
                "west"  : __DIR__"minju1",
        ]));
        set("objects", ([
                __DIR__"npc/kid" : 3,
        ]));

        set("coor/x", -12250);
	set("coor/y", 820);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}