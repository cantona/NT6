// Room: /d/jiaxing/yanyu.c
// Last Modified by winder on Nov. 17 2000

inherit ROOM;

void create()
{
        set("short", "煙雨樓");
        set("long", @LONG
煙雨樓建在南湖中心的一個小島上。南湖終年不斷的水氣把它籠罩
得迷迷濛濛的。樓內是家飯店。
LONG );
        set("outdoors", "jiaxing");
        set("exits", ([
                "up"    : __DIR__"yanyu2",
                "north" : __DIR__"nanhu1",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer" : 1
        ]));
//        set("no_clean_up", 0);
	set("coor/x", 1210);
	set("coor/y", -1790);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}