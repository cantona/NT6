// Room: /d/quanzhou/westroad2.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "刺桐西路");
        set("long", @LONG
這是泉州的主要幹道，筆直寬廣，車水馬龍，熱鬧非凡。北邊是開
元寺，南邊是濟世堂老店，西邊則是西門吊橋。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "west"  : __DIR__"westbridge",
                "east"  : __DIR__"westroad1",
                "north" : __DIR__"kaiyuansi",
                "south" : __DIR__"jishitang",
        ]));
	set("coor/x", -920);
	set("coor/y", -7670);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}