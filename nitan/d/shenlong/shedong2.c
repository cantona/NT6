inherit DEMONROOM;

void create()
{
        set("short", "毒蛇窟");
        set("long",@LONG
這是蛇洞內的毒蛇窟，只見四周滿是毒蛇，恐怖非常。
LONG);

	set("exits", ([
		"east"  : __DIR__"shedong1", 
		"west"  : __DIR__"shedong2.1",

	]));

		set("n_time", 15); 
		set("n_npc", 3); 
		set("n_max_npc", 8);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/xuanmang");

        setup();
}
