// Room: /d/huanggong/gong7.c

inherit ROOM;

void create()
{
        set("short", "鐘粹宮");
        set("long", @LONG
這裡已是深宮內院. 陳列著一些工藝美術, 這就是後妃嬪女居住的
地方. 進了這兒可以深深感受到何謂“一入宮門深似海”.
LONG
        );
        set("objects", ([
                __DIR__"npc/gongnv" : 1,
        ]));
        set("exits", ([ /* sizeof() == 1 */
                "east"  : __DIR__"tinglang4",
                "south" : __DIR__"gong9",
        ]));

	set("coor/x", -2800);
	set("coor/y", 7781);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}