inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在衡山山路上，四望山峰錯落，林壑幽深，溪泉飛瀑，雲霧
繚繞，不覺心胸大快。再走一會兒就是半山亭了。
LONG );
        set("exits", ([ 
               "southup"    : __DIR__"chidifeng",
               "northwest"  : __DIR__"shanlu4",
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6900);
	set("coor/y", -5570);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
 