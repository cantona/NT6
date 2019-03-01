inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在衡山山路上，四望山峰錯落，林壑幽深，溪泉飛瀑，雲霧
繚繞，不覺心胸大快。南邊山路就是 磨鏡台 和 天柱峰。
LONG );
        set("exits", ([
                "southdown"  : __DIR__"mojingtai",
                "east"       : __DIR__"shanlu5",
                 "west"       : __DIR__"shulin1",
        ]));

        set("objects", ([
                __DIR__"npc/xiangke"  : 4,
                __DIR__"npc/youke"    : 2,
        ]));    

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6950);
	set("coor/y", -5540);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}