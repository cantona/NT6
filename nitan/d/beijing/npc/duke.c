inherit NPC;

void create()
{
        set_name("賭客", ({ "du ke", "du", "ke" }) );
        set("gender", "男性" );
        set("age", 40);
        set("long",
              "一個正賭得興高採烈的賭客。\n");
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
                "賭客麻道：他媽的，今天手氣怎麼那麼不順？\n",
        }) );       

        setup();
        carry_object("/d/beijing/npc/obj/cloth")->wear();
        add_money("coin", 30);
}
