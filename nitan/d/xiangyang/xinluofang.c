// Room: /d/xiangyang/xinluofang.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "新羅坊");
        set("long", @LONG
新羅坊，顧名思義是給新羅人住的地方，不過其實現在新羅已經
被高麗所滅掉，這裏應該叫做高麗坊的。可是大家已經習慣了，於是
便還這麼叫。這裏住着許多高麗商人，也有些高麗的使臣進東京城路
過襄陽，便也住在這裏。這裏的高麗商人總有很多很好的貨物，大家
都喜歡來買，於是這裏就非常的熱鬧了。
LONG );
        set("exits", ([
                "south" : __DIR__"northroad1",
        ]));
        set("objects", ([
                __DIR__"npc/gaoli" : 1,
        ]));
        set("coor/x", -7820);
	set("coor/y", -730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}