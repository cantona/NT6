inherit ROOM;

void create()
{
        set("short", "育嬰堂");
        set("long", @LONG
走進育嬰堂，你看見到處都是一些小孩子，一位中年婦女正在照看着
這些小孩子，原來這裏是替人看孩子的地方，洛陽當地有些夫婦因為沒有
時間照看自己的孩子，就把他們送到這裏來，有專人看管。育嬰堂裏充滿
了小孩子們的啼哭和喧鬧聲。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"eroad3",
        ]));
        set("objects", ([
                "/d/beijing/npc/girl2" : 1,
                "/d/beijing/npc/kid1" : 1,
                "/d/beijing/npc/girl4" : 1,
                "/d/beijing/npc/boy2" : 1,
        ]));
	set("coor/x", -6960);
	set("coor/y", 2140);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}