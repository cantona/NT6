inherit DEMONROOM;

void create()
{
        set("short", "沙地");
        set("long",@LONG
這是神龍島東部的一片沙地。
LONG);

	set("exits", ([
		"west"  : __DIR__"lin1.16", 
		"east"  : __DIR__"haitan2",

	]));

		set("n_time", 30); 
		set("n_npc", 2); 
		set("n_max_npc", 3);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/jinshewang");

        set("outdoors", "shenlong");
        setup();
}
