inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在衡山山路上，四望山峯錯落，林壑幽深，溪泉飛瀑，雲霧
繚繞，不覺心胸大快。
LONG );
        set("exits", ([ 
               "southdown"  : __DIR__"beimen",
               "northwest"  : __DIR__"shanlu2",
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6890);
	set("coor/y", -5600);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}