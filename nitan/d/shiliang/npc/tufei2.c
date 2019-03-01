// tufei2.c

inherit NPC;

void create()
{
        set_name("土匪", ({ "tufei","bandit","fei" }) );
        set("gender", "男性");
        set("age", 20);
        set("long",
                "這傢伙滿臉橫肉一付凶神惡煞的模樣，令人望而生畏。\n");
        set("combat_exp", 5000);
        set("shen_type", -1);
        set("attitude", "aggressive");

        set("apply/attack", 10);
        set("apply/defense", 10);

//        set("chat_chance", 30);
//        set("chat_msg", ({
//                "土匪一聲大喊: 此山是我開，此樹是我栽，若要從此過，留下買路財 !\n",
//        }) );

        set_skill("unarmed", 25);
        set_skill("parry", 20);
        set_skill("dodge", 20);

        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 10);
}