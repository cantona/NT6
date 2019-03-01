inherit NPC;

void create()
{
        set_name("閒人", ({ "xian ren", "xian", "ren" }) );
        set("gender", "男性" );
        set("age", 32);
        set("long",
              "一個在街上閒逛的遊人。\n");
        set("shen_type", 1);
        set("combat_exp", 10000);
        set("str", 17);
        set("dex", 20);
        set("con", 17);
        set("int", 22);
        set("attitude", "peaceful");
        set_skill("dodge",20);
        set_skill("unarmed",20);
        set("chat_chance", 1);
        set("chat_msg", ({
                "閒人低聲嘀咕了一聲。\n",
        }) );

        setup();
        carry_object("/clone/cloth/cloth")->wear();
        add_money("coin", 30);
}
