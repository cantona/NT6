inherit NPC;

void create()
{
        set_name("園丁", ({ "yuan ding", "yuan", "ding" }) );
        set("gender", "男性" );
        set("age", 22);
        set("long",
                "一個種植栽培花草的園丁。\n");
        set("shen_type", 1);
        set("combat_exp", 2000);
       set("str", 10);
       set("dex", 10);
       set("con", 10);
       set("int", 10);
        set("attitude", "peaceful");
       set_skill("dodge",20);
       set_skill("unarmed",20);
       set("chat_chance", 1);
       set("chat_msg", ({
                "園丁弓著腰整理著花草。\n",
        }) );       

        setup();
       carry_object("/d/beijing/npc/obj/cloth")->wear();
        add_money("silver", 1);
}
