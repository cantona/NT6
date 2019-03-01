inherit ROOM;
void create()
{
        set("short", "藏經殿");
        set("long", @LONG
藏經殿深掩祥光峰下，因為藏明太祖所贈「大藏經」故名。只見
這裡古木參天，殿宇飄翼，奇花異草，林壑幽深，景色秀麗，「藏經
殿之秀」是衡山大四絕之一。
LONG );
        set("exits", ([
               "east"   : __DIR__"shanlu14",
               "south"  : __DIR__"shuzhuangtai",
        ]));

        set("no_clean_up", 0);

	set("coor/x", -6960);
	set("coor/y", -5510);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}