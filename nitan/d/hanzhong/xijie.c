// xijie.c 西街
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "西街");
        set("long", @LONG
漢中鎮的西面是貧苦百姓的聚居區，西街比起其他幾條街道來也
顯得破朽雜亂得多。街南面是一座年久失修的小廟，已經搖搖欲墜了。
北面是一户低矮的茅屋，西面是漢中的西門。從這裏轉而往東，就走
到漢中鎮的中心了。
LONG
        );
        set("outdoors", "hanzhong");
        set("exits", ([
                "east" : __DIR__"zhongxin",
                "north" : __DIR__"minju2",
                "south" : __DIR__"xiaomiao",
                "west" : __DIR__"ximen",
        ]));
        set("objects", ([
                __DIR__"npc/punk" : 1,
                "/clone/npc/walker"  : 1,
        ]));

        set("coor/x", -12260);
	set("coor/y", 810);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}