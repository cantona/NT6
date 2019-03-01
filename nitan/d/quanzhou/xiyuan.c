// Room: /d/quanzhou/xiyuan.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "戲院");
        set("long", @LONG
這裡是南方戲曲中心，四面八方的戲迷每天都湧入此地一睹為快。
戲院裡戲種繁多，曲目精彩。計有南音，梨園戲，提線木偶，高甲戲等
飲譽四方的珍貴藝術。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "southeast" : __DIR__"zhaiqu2",
                "east"      : __DIR__"zhaiqu1",
        ]));
	set("coor/x", -920);
	set("coor/y", -7680);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}