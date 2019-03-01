inherit DEMONROOM;

void create()
{
        set("short", "東部叢林危險地帶");
        set("long",@LONG
這是神龍島原始叢林深處，再往前走就是危險地帶了，小心。
LONG);

	set("exits", ([
		"east"  : __DIR__"lin1.16", 
		"west"  : __DIR__"lin1.14",

	]));

		set("n_time", 30); 
		set("n_npc", 1); 
		set("n_max_npc", 1);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/qingshe");

        set("outdoors", "shenlong");
        setup();
}
