inherit NPC;

void create()
{
        set_name("戲子", ({ "xi zi", "xi", "zi" }) );
        set("gender", "男性" );
        set("age", 32);
        set("long",
              "一個在戲院唱戲的戲子。\n");
        set("shen_type", 1);
        set("combat_exp", 10000);
        set("str", 17);
        set("dex", 20);
        set("con", 17);
        set("int", 22);
        set("attitude", "peaceful");
        set_skill("dodge",20);
        set_skill("unarmed",20);

        setup();
        carry_object("/clone/cloth/cloth")->wear();
        add_money("coin", 30);
}
