inherit NPC;


void create()
{
        set_name("進香客", ({ "jinxiang ke","ke" }) );
        set("gender", "女性" );
        set("age",60);
	set_xiuwei("unarmed", random(200) );
        set("combat_exp",2000);
        set("social_exp",2000);
        setup();    
	carry_object(__DIR__"obj/linen")->wear();
        add_money("coin",10);
}
