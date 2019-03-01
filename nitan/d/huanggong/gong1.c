// Room: /d/huanggong/gong1.c

inherit ROOM;

void create()
{
        set("short", "長春宮");
        set("long", @LONG
這裡已是深宮內院. 陳列著一些工藝美術, 這就是後妃嬪女居住的
地方. 進了這兒可以深深感受到何謂“一入宮門深似海”. 宮中掛著一
個紅木牌匾: "茂修內治".
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
                "east"  : __DIR__"tinglang1",
                "south" : __DIR__"gong3",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -2840);
	set("coor/y", 7781);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}