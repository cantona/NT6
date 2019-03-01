inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在衡山山路上，四望山峰錯落，林壑幽深，溪泉飛瀑，雲霧
繚繞，不覺心胸大快。抬頭只見不遠處有一個亭子。
LONG );
        set("exits", ([
               "southeast" : __DIR__"shanlu3",
               "northup"   : __DIR__"banshan",
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6910);
	set("coor/y", -5560);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}