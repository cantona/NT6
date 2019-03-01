inherit NPC;



void create()
{
        set_name("少年弈者", ({ "yi zhe","zhe" }) );
        set("gender", "男性" );
        set("age", 16);
        set("str", 26);
        set("cor", 40);
        set("cps", 40);
        set("per", 40);
        set("int", 40);
        set("team_member",({
                "yi zhe",
                }) );

        set("attitude", "peaceful");

        set("force_factor", 1);
        set("max_gin", 200);
        set("max_kee", 200);
        set("max_sen", 200);
        set("eff_gin", 200);
        set("eff_kee", 200);
        set("eff_sen", 200);
        set("gin", 200);
        set("kee", 200);
        set("sen", 200);
        set("max_force", 500);
        set("force", 500);

        set("long",     "一名稚氣未乾而聰明伶俐的少年。\n");


        set("combat_exp", 20000);
        set_wugong("force",40,40,0);
	set_wugong("shizi-zhan", 120, 120, 1);
    //set_wugong("kd-xinfa",40,40,0);
    //set_wugong("ny-bufa",40,40,1);
	set_xiuwei("unarmed", 700);
	set_xiuwei("dodge", 600);

        set("positive_score",100);
        setup();

        carry_object(__DIR__"obj/yifu4")->wear();
}
int refuse_killing(object ob)
{
        message_vision("那少年對$N叱道：“惡賊安敢如此，給我拿下！”\n",ob);
        return 0;
}
