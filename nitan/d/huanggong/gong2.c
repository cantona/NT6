// Room: /d/huanggong/gong2.c

inherit ROOM;

void create()
{
        set("short", "儲秀宮");
        set("long", @LONG
這裏已是深宮內院. 陳列着一些工藝美術, 這就是后妃嬪女居住的
地方. 進了這兒可以深深感受到何謂“一入宮門深似海”. 宮門上掛着
一個鑲邊匾額:  "懿恭婉順".
LONG
        );
        set("exits", ([ /* sizeof() == 4 */
                "west"  : __DIR__"tinglang1",
                "south" : __DIR__"gong4",
        ]));
        set("objects", ([ /* sizeof() == 4 */
                 __DIR__"npc/taohongying": 1,
        ]));

	set("coor/x", -2820);
	set("coor/y", 7781);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}