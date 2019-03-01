// xianghuo.c 香火道人

inherit NPC;

void create()
{
        set_name("香火道人", ({ "xianghuo daoren","daoren","xianghuo"}));
        set("age", 32);
        set("gender", "男性");
        set("long",
"武當派四方香火的弟子。\n");
        set("attitude", "peaceful");
        set("str", 24);
        set("dex", 16);
        set("combat_exp", 50000);
        set("shen_type", 1);

        set_skill("unarmed", 60);
        set_skill("dodge", 60);
        set_skill("parry", 60);
        set_skill("force", 60);
        set_temp("apply/attack", 40);
        set_temp("apply/defense", 40);
        set_temp("apply/damage", 20);
        set_temp("apply/armor", 30);
        set("chat_chance", 5);
        set("chat_msg", ({
                "香火道人把手舉到你面前：給點香火錢吧，無量壽佛！\n",
                (: random_move :)
        }) );
        create_family("武當派", 4, "弟子");
        setup();
        carry_object("/clone/weapon/changjian");
        carry_object("/d/wudang/obj/whiterobe")->wear();
}
