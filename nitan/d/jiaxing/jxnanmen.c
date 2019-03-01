// Room: /d/jiaxing/jxnanmen.c
// Last Modified by winder on Nov. 17 2000

inherit ROOM;

void create()
{
        set("short", "嘉興南門");
        set("long", @LONG
這裡是嘉興的南門。周圍長著茂密的竹林。東面是座廟宇。向南可
入福建。向東南就是號稱天堂的杭州城了。
LONG );
        set("exits", ([
                "north"    : __DIR__"jiaxing",
                "east"     : __DIR__"tieqiang",
                "south"    : __DIR__"jnroad4",
                "southeast": "/d/hangzhou/road1",
                "southwest": __DIR__"majiu",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "jiaxing");
	set("coor/x", 1190);
	set("coor/y", -1780);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}