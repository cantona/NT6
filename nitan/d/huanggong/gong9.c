// Room: /d/huanggong/gong9.c

inherit ROOM;

void create()
{
        set("short", "承乾宮");
        set("long", @LONG
這裏已是深宮內院. 陳列着一些工藝美術, 這就是后妃嬪女居住的
地方. 進了這兒可以深深感受到何謂“一入宮門深似海”. 宮裏陳設奢
華, 引人注目的是堂上的"勤襄內政"匾額.
LONG
        );
        set("objects", ([
                __DIR__"npc/gongnv" : 1,
        ]));
        set("exits", ([ /* sizeof() == 4 */
                "west"  : __DIR__"kunninggong",
                "east"  : __DIR__"tinglang5",
                "north" : __DIR__"gong7",
                "south" : __DIR__"gong11",
        ]));

	set("coor/x", -2800);
	set("coor/y", 7771);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}