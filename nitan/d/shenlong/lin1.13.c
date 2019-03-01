inherit DEMONROOM;

void create()
{
        set("short", "東部叢林");
        set("long",@LONG
這是一片原始叢林，陽關被四周高聳的樹木遮蔽，異常陰暗。
LONG);

	set("exits", ([
		"east"  : __DIR__"lin1.14", 
		"west"  : __DIR__"lin1.12",

	]));


		
		set("n_time", 30); 
		set("n_npc", 2); 
		set("n_max_npc", 6);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/yanjingshe");

        set("outdoors", "shenlong");
        setup();
}
