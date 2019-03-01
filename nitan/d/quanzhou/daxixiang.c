// Room: /d/quanzhou/daxixiang.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "打錫巷");
        set("long", @LONG
這是普普通通的一條石板小路。走在上面，也許你根本想不到這是
施琅將軍攻克台灣後為顯其戰功，將其城池的砌石運回舖成此路。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "west" : __DIR__"southroad1",
                "east" : __DIR__"jiangjunfu",
        ]));
	set("coor/x", -890);
	set("coor/y", -7680);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}