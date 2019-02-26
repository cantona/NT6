// Room: /d/quanzhou/zahuopu.c

inherit ROOM;

void create()
{
        set("short", "雜貨鋪");
        set("long", @LONG
這裏是一家專賣女人用的東西的小鋪子。
LONG );
        set("exits", ([
                "east" : __DIR__"xiangyang",
        ]));
        set("objects", ([
                __DIR__"npc/chen" : 1,
        ]) );
	set("coor/x", -110);
	set("coor/y", -6200);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}