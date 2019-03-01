// Room: /d/huanggong/gong10.c

inherit ROOM;

void create()
{
        set("short", "永和宮");
        set("long", @LONG
這裡已是深宮內院. 陳列著一些工藝美術, 這就是後妃嬪女居住的
地方. 進了這兒可以深深感受到何謂“一入宮門深似海”.
LONG
        );
        set("objects", ([
                __DIR__"npc/gongnv" : 1,
                __DIR__"npc/hui" : 1,
        ]));
        set("exits", ([ /* sizeof() == 2 */
                "west"  : __DIR__"tinglang5",
                "south" : __DIR__"gong12",
                "north" : __DIR__"gong8",
        ]));

	set("coor/x", -2780);
	set("coor/y", 7771);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}