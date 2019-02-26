// Room: southroad1.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "南大街");
        set("long", @LONG
你走在南大街上，踩着堅實的青石板地面。這裏顯得熱鬧多了。
東北方向是東大街，往西一直走都是南大街。東南方向傳來陣陣喧鬧，
那裏有個客店，杏簾分明： 錦城驛。
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
            "northeast"  : __DIR__"eastroad3",
            "southeast"  : __DIR__"kedian",
            "west"       : __DIR__"southroad2",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -15210);
	set("coor/y", -1850);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}