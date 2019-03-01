inherit DEMONROOM;

void create()
{
        set("short", "蛇洞外");
        set("long",@LONG
這是神龍島蛇洞外，據說洞內毒蛇遍布，洞中住有蛇精，沒有人進去後
能再活著出來。
LONG);

	set("exits", ([
		"north"   : __DIR__"dong2.15",
		"enter"   : __DIR__"shedong1",

	]));

		set("n_time", 30); 
		set("n_npc", 2); 
		set("n_max_npc", 6);
		set("s_npc", "/clone/dream_npc/shenlongdao/xixue-bianfu");

        setup();
}
