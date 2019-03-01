inherit DEMONROOM;

void create()
{
        set("short", "九洲");
        set("long",@LONG
深切哀悼在9﹒18事變中犧牲的烈士，為我們的英雄報仇吧！
LONG);

	set("exits", ([
		"south"   : __DIR__"jiuzhou1",
	]));

		set("n_time", 30); 
		set("n_npc", 5); 
		set("n_max_npc", 15);
		set("s_npc", "/clone/dream_npc/japangame/japannpc01");

        setup();
}
