// Room: /d/huanggong/gong8.c

inherit ROOM;

void create()
{
        set("short", "景陽宮");
        set("long", @LONG
這裏已是深宮內院. 陳列着一些工藝美術, 這就是后妃嬪女居住的
地方. 進了這兒可以深深感受到何謂“一入宮門深似海”. 宮裏掛着一
個皇宮中常見的匾額: "敬修內則".
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
                "west"  : __DIR__"tinglang4",
                "south" : __DIR__"gong10",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -2780);
	set("coor/y", 7781);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}