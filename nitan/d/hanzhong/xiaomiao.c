// xiaomiao.c 土地廟
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "土地廟");
        set("long", @LONG
這座廟宇原本是武功鎮中的土地廟，不過因為很久沒有修繕過，
已經破爛不堪。土地爺的金身也只剩下了半截，供桌只剩下了三條
腿，窗框已經全被下光了，被附近的貧苦百姓拿回家去生火取暖。
這裡平常是沒有人來的，只有一些遊手好閒的地痞流氓之類把這裡
當做了家。
LONG
        );
        set("exits", ([
                "north" : __DIR__"xijie",
        ]));

        set("objects", ([
                __DIR__"npc/dipi" : 1,
        ]));

        set("coor/x", -12260);
	set("coor/y", 800);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}