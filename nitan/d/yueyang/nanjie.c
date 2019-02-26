// Room: /d/yueyang/nanjie.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "南街");
        set("long", @LONG
這是一條又長又寬的青石大道，東邊是客店，西邊是飯店，這裏是
南來北往的客商必到之處，因此也是全城最熱鬧的地方。兩邊的小二在
屋檐下不停地招攬生意，一些流氓和不成器的乞丐們也混在其中乘機揩
油，大姑娘喊，小媳婦鬧，響成一片。
LONG );
        set("outdoors", "yueyang");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"kedian",
                "west"  : __DIR__"jiudian",
                "north" : __DIR__"zhongxin",
                "south" : __DIR__"nanmen",
        ]));
        set("objects", ([
                CLASS_D("gaibang")+"/liu-zhuzhuang" : 1,
        ]));
	set("coor/x", -6200);
	set("coor/y", -3020);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}