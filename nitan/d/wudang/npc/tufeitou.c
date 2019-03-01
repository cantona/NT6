// tufeitou.c

inherit NPC;

void create()
{
        set_name("土匪頭", ({ "tufei tou","bandit leader","tou" }) );
        set("gender", "男性");
        set("age", 45);
        set("long",
                "這家伙滿臉殺氣，一付兇神惡煞的模樣，令人望而生畏。\n");
        set("combat_exp", 20000);
        set("shen_type", -1);
        set("attitude", "aggressive");

        set("apply/attack",  30);
        set("apply/defense", 30);

        set("chat_chance", 5);
        set("chat_msg", ({
                "土匪頭嘿嘿地冷笑著: 今天你就別想從這裡活著出去了!\n",
        }) );

        set_skill("sword", 30);
        set_skill("unarmed", 50);
        set_skill("parry", 50);
        set_skill("dodge", 50);

        setup();
        carry_object("/d/city/obj/changjian")->wield();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 100);
}