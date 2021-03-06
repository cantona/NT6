// Room: /d/xiangyang/jiekou1.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "大街口");
        set("long", @LONG
因為這兒是十字街口，所以非常熱鬧。小商小販們在向行人吆喝
着，兜售他們的商品。雖然襄陽飽受蒙古軍侵擾，但這兒看不出人們
有絲毫的緊張，好像他們已司空見慣、習以為常了。北面和西面是胡
同，許多襄陽城的老百姓住在裏面，東面和南面是青石鋪就的大街。
LONG );
        set("outdoors", "xiangyang");

        set("exits", ([
                "east"  : __DIR__"northroad1",
                "south" : __DIR__"westroad2",
                "west"  : __DIR__"hutong1",
                "north" : __DIR__"hutong2",
        ]));
        set("objects", ([
                "/d/village/npc/seller" : 1,
        ]));
        set("coor/x", -7830);
	set("coor/y", -740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}