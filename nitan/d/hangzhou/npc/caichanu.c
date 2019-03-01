// caichanu.c

inherit NPC;

void create()
{
        set_name("採茶女", ({ "girl" }) );
        set("gender", "女性" );
        set("age", 19);
        set("per", 40);
        set("long", "江南清秀的採茶姑娘一樣楚楚動人。\n");
        set("combat_exp", 700);
        set("attitude", "friendly");
        set_skill("unarmed", 40);
        set_skill("parry", 25);
        set_skill("dodge", 30);

        set("chat_chance", 5);
        set("chat_msg", ({
            "採茶女說道：儂今早去廟裡上香伐，帶我一道去好勿好？\n",
        }) );

        setup();
        add_money("silver", 15);
        carry_object("/clone/cloth/cloth")->wear();
}
