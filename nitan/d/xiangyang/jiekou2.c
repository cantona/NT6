// Room: /d/xiangyang/jiekou2.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "大街口");
        set("long", @LONG
因為這兒是十字街口，所以非常熱鬧。小商小販們在向行人吆喝
著，兜售他們的商品。雖然襄陽飽受蒙古軍侵擾，但這兒看不出人們
有絲毫的緊張，好象他們已司空見慣、習以為常了。北面是小胡同，
許多襄陽城的老百姓住在裡面，南面和西面是青石舖就的大街。東邊
就是大名鼎鼎的無極幫總部。
LONG );
        set("outdoors", "xiangyang");

        set("exits", ([
                "east"  : __DIR__"xiaorong1",
                "south" : __DIR__"eastroad2",
                "west"  : __DIR__"northroad2",
                "north" : __DIR__"xiaorong2",
        ]));
        set("objects", ([
                __DIR__"npc/kid" : 1,
                "/d/village/npc/seller" : 1,
        ]));
        set("coor/x", -7790);
	set("coor/y", -740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}