// Room: /d/huanggong/ningshougong.c

inherit ROOM;

void create()
{
        set("short", "寧壽宮");
        set("long", @LONG
這裡是太上皇起居休憩的地方。現下卻是公主寢宮。只見牆壁上、
桌椅上，都是刀劍皮鞭之類的兵器，便如是個武人的居室，哪裡像是金
枝玉葉的公主寢室。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
                 "north" : __DIR__"changyinge",
                 "south" : __DIR__"huangjidian",
        ]));
        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/jianning" : 1,
        ]));

	set("coor/x", -2790);
	set("coor/y", 7771);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}