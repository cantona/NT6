inherit NPC;

void create()
{
        set_name("賣藝人", ({ "maiyi ren", "ren" }) );
        set("gender", "男性" );
        set("age", 25);
        set("long",
              "一個沿街賣藝的人。\n");
        set("shen_type", 1);
        set("combat_exp", 10000);
        set("str", 20);
        set("dex", 20);
        set("con", 20);
        set("int", 20);
        set("attitude", "peaceful");
        set_skill("dodge",20);
        set_skill("unarmed",20);
        set("chat_chance", 1);
        set("chat_msg", ({
                 "賣藝人大聲叫道：俺給大家表演俺的絕活。\n",
        }) );       

        setup();
        carry_object("/d/beijing/npc/obj/cloth")->wear();
        add_money("silver", 10);
}
