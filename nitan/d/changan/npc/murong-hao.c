//murong-hao.c

inherit BUNCHER; 
inherit F_DEALER;

void create()
{
        set_name("慕容豪", ({"murong hao", "murong", "hao"}));
        set("title", "老闆");
        set("gender", "男性");
        set("age", 25);
        set("long", "慕容豪是慕容世家的弟子。\n");
        set("combat_exp", 90000);
        set("attitude", "heroic"); 
        set_skill("sword", 50);
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_skill("parry", 50);
        set("force", 200);
        set("max_force", 200);
        set("force_factor", 5);
        set("vendor_goods", ({
                "/d/changan/npc/obj/changjian",
                "/d/changan/npc/obj/hammer",
        }));

        setup();
        carry_object("/d/changan/npc/obj/jinzhuang")->wear();
        carry_object("/d/changan/npc/obj/changjian")->wield();
}

void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) && !is_fighting()) 
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

void greeting(object ob)
{
        if (! ob || ! visible(ob) || environment(ob) != environment())
                return;
        say(name() + "漫不經心的看了你一眼，順手拿起了身旁"
            "的一把長劍用衣袖拭了拭。\n");
}

int accept_fight(object me)
{
        command("say 他媽的！你一進來老子就知道你是衝着我來的！\n");   
        command("hate");
        command("grin");
        command("say 我不是好欺負的！"+RANK_D->query_rude(me)+"你拿命來吧！");
        command("kill"+query("id", me));

        return 1;
}
