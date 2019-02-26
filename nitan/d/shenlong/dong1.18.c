inherit DEMONROOM;

void create()
{
        set("short", "寒冰洞外");
        set("long",@LONG
這裏是神龍島一處隱祕的洞穴，此處略覺寒冷，據説洞內藏有各種怪獸，
傳説一隻巨大的冰龍就住在這洞內，但是沒人見過。。
LONG);

	set("exits", ([
		"east"   : __DIR__"dong1.17",
                //"enter"   : __DIR__"bingdong1",

	]));

		set("n_time", 30); 
		set("n_npc", 1); 
		set("n_max_npc", 3);
		set("s_npc", "/clone/dream_npc/shenlongdao/xixue-bianfu");

        setup();
}
