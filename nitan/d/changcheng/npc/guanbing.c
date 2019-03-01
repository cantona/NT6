// guanbing.c 官兵

inherit NPC;

void create()
{
        set_name("官兵", ({ "guan bing", "bing" }));
        set("age", 22);
        set("gender", "男性");
        set("long", "這就是守衛邊疆的官兵，雖然他們年紀不大，由于長年的風吹日曬，使他們顯得很蒼老。\n");
        set("attitude", "peaceful");
//        set("vendetta_mark", "authority");
//      set("pursuer", 1);

        set("str", 24);
        set("dex", 16);
        set("combat_exp", 10000);
        set("shen_type", 1);

        set_skill("unarmed", 40);
        set_skill("dodge", 40);
        set_skill("parry", 40);
        set_skill("blade", 40);
        set_skill("force", 40);
        set_temp("apply/attack", 40);
        set_temp("apply/defense", 40);
        set_temp("apply/damage", 20);
        set_temp("apply/armor", 40);

//        if (random(2) == 1) {
//                set("chat_chance", 10);
//                set("chat_msg", ({
//                        (: random_move :),
//                }));
//        }

        set("chat_chance", 10);
        set("chat_msg", ({
                "官兵大聲喝道：大膽，竟敢造反不成？\n",
                "官兵嘆了口氣：唉，很久沒有回家了，不知道她怎麼樣了？\n",
                "官兵大聲說道：只要有我在這裡就沒有人能打過去！\n",
        }));
        setup();
        carry_object("/d/city/obj/gangdao")->wield();
        carry_object("/d/city/obj/junfu")->wear();
}

void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player()) && 
                (int)ob->query_condition("killer")) {
                remove_call_out("kill_ob");
                call_out("kill_ob", 1, ob);
        }
}

int accept_fight(object me)
{
        command("say 大爺我正想找人殺吶，今天算你倒霉。\n");
        me->apply_condition("killer", 500);
        kill_ob(me);
        return 1;
}