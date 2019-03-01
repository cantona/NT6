// youke.c

inherit NPC;



void create()
{
	set_name("遊客", ({ "you ke","ke"}));
	if ( random(10) < 7 )
	    set("gender", "男性" );
	else
	    set("gender", "女性" );
	set("age", 15+random(50));
	set("long",
		"這是一位到崆峒山來遊玩的遊客。\n");
	set("chat_chance", 10);
    set("chat_msg", ({
        (: random_move :)
    }));
	set("combat_exp", 600+random(400));
    set("social_exp", 600+random(400));
	set("attitude", "friendly");
    set_temp("apply/attack",20+random(100) );
    set_temp("apply/defense",20+random(100) );
    set_temp("apply/damage",random(5) );
    set_temp("apply/armor",random(5) );
	setup();
    if ( query("gender") == "男性")
      	carry_object(__DIR__"obj/yifu1")->wear();
    else 
        carry_object(__DIR__"obj/yifu3")->wear();
	add_money("coin", 100);
	set("score",5-random(10));
}

