//xtong2.c 小童

inherit NPC;

void create()
{
	set_name("小童", ({ "xiao tong", "xiao","tong"}) );
	set("gender", "男性" );
	set("age", 16);
	set("long",
		"這是一個青衣小童，正拿着扇子對着爐子煽着。\n");
	set("combat_exp", 50000);
	set("attitude", "friendly");
	setup();
        carry_object("/clone/cloth/cloth")->wear();
        add_money("silver",random(50));
}