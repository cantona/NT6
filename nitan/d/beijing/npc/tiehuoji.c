inherit NPC;

void create()
{
        set_name("鐵匠舖伙計", ({ "huoji" }) );
        set("gender", "男性" );
        set("age", 18);
        set("long",
              "一個十多歲的青年，在鐵匠舖當學徒。\n");
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

        setup();
        carry_object("/d/beijing/npc/obj/cloth")->wear();
        add_money("coin", 30);
}
