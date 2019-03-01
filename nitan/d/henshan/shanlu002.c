inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在衡山山路上，四望山峰錯落，林壑幽深，溪泉飛瀑，雲霧
繚繞，不覺心胸大快。一直往西可通往磨鏡台和天柱峰。 
LONG );
        set("exits", ([ 
                "southeast"  : __DIR__"banshan",
                "west"       : __DIR__"shanlu001",    
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6920);
	set("coor/y", -5540);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}