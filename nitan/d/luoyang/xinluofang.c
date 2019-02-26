inherit ROOM;

void create()
{
        set("short", "新羅坊");
        set("long", @LONG
新羅坊，顧名思義是給新羅人住的地方，不過其實現在新羅已經被高
麗所滅掉，這裏應該叫做高麗坊的。可是大家已經習慣了，於是便還這麼
叫。這裏住着許多高麗商人，也有些高麗的使臣進東京城路過襄陽，便也
住在這裏。這裏的高麗商人總有很多很好的貨物，大家都喜歡來買，於是
這裏就非常的熱鬧了。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"wroad1",
        ]));
        set("objects", ([
                "/d/xiangyang/npc/gaoli" : 1,
        ]));
	set("coor/x", -7000);
	set("coor/y", 2190);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}