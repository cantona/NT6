inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在衡山山路上，四望山峰錯落，林壑幽深，溪泉飛瀑，雲霧
繚繞，不覺心胸大快。西邊上山的路。東邊隱隱聽到水響。
LONG );
        set("exits", ([ 
               "west"    : __DIR__"shanlu11",
               "eastup"  : __DIR__"shuiliandong",
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6880);
	set("coor/y", -5580);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}