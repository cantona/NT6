// bing.c 官兵

inherit NPC;

void create()
{
        set_name("回族兵", ({ "guan bing", "bing" }));
        set("age", 32);
        set("gender", "男性");
        set("long", "他是個戍邊多年的老兵。年紀不小了，但尚未成家。\n");
        set("attitude", "peaceful");
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


        set("chat_chance_combat", 10);
        set("chat_msg_combat", ({
                "回族官兵喝道：大膽刁民，竟敢造反不成？\n",
                "回族官兵喝道：跑得了和尚跑不了廟，你還是快快束手就擒！\n",
        }));
        setup();
        carry_object(__DIR__"obj/gangdao")->wield();
        carry_object(__DIR__"obj/junfu")->wear();
}

int accept_fight(object me)
{
        command("say 大爺我守邊關累得要死，沒空和" + RANK_D->query_respect(me)
                + "過招玩。\n");
        return 0;
}
