inherit ROOM;

void create()
{
        set("short", "青石大道");
        set("long", @LONG
你走在一條青石大道上，四周靜悄悄的。
LONG );
	set("outdoors", "sanbuguan");
        set("exits", ([
                "south" : __DIR__"wdroad4",
                "north" : __DIR__"wdroad2",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
