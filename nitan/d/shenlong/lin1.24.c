inherit DEMONROOM;

void create()
{
        set("short", "神祕巖洞冰窖");
        set("long",@LONG
這是神龍島東南部巖洞深處的一個冰窖，這裏異常寒冷。
LONG);

	set("exits", ([
		"south"  : __DIR__"lin1.25", 
		"north"  : __DIR__"lin1.23",

	]));

		set("n_time", 30); 
		set("n_npc", 1); 
		set("n_max_npc", 6);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/xuanmang");

        setup();
}
