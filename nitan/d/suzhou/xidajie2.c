// Room: /d/suzhou/xidajie2.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "西大街");
        set("long", @LONG
你走在西大街上，感到這裏的街面要比別處的乾淨、整潔。大概因
為靠近衙門、兵營可受保護的緣故，富人們都喜歡住在這裏。東邊靜悄
悄地沒有幾個行人，西邊是西城門通往郊外。南邊是玄妙觀，北邊是一
個書堂。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "east"      : __DIR__"xidajie1",
                "west"      : __DIR__"ximen",
                "north"     : __DIR__"shuchang",
                "south"     : __DIR__"xuanmiao",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
	set("coor/x", 1090);
	set("coor/y", -1060);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}