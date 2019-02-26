// Room: /d/huanggong/gong3.c

inherit ROOM;

void create()
{
        set("short", "體元殿");
        set("long", @LONG
這裏已是深宮內院. 陳列着一些工藝美術, 這就是后妃嬪女居住的
地方. 進了這兒可以深深感受到何謂“一入宮門深似海”.
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
                "east" : __DIR__"tinglang2",
                "north" : __DIR__"gong1",
                "south" : __DIR__"gong5",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -2840);
	set("coor/y", 7771);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}