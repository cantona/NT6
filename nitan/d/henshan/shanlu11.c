inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在衡山山路上，四望山峰錯落，林壑幽深，溪泉飛瀑，雲霧
繚繞，不覺心胸大快。西邊上山是赤帝峰。東邊遠遠可以看到衡山五
峰之一的紫蓋峰了。
LONG );
        set("exits", ([ 
               "westup"  : __DIR__"chidifeng",
               "east"    : __DIR__"shanlu12",
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6890);
	set("coor/y", -5580);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}