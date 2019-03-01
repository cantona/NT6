// alabo.c
// Last Modified by winder on May. 29 2001

inherit NPC;

void create()
{
        set_name("阿拉伯商人", ({ "alabo shangren", "shangren", "trader" }));
        set("gender", "男性");
        set("age", 35);
        set("long","一個阿拉伯商人。頭上包著一塊白巾。\n");
        set("attitude", "friendly");
        set("combat_exp", 6000);
        set("shen_type", 1);
        set_skill("unarmed", 30);
        set_skill("blade", 40);
        set_skill("parry", 30);
        set_skill("dodge", 40);

        set_temp("apply/attack", 15);
        set_temp("apply/defense", 15);
        set_temp("apply/damage", 20);

        setup();
        set("chat_chance", 15);
        set("chat_msg", ({
                "阿拉伯商人對你擠了一下眼睛。\n",
                "阿拉伯商人對你說：阿薩蘭馬離貢，穆罕默德瑞素阿拉。你沒聽懂。\n",
                (: random_move :)
        }) );
        carry_object("/clone/weapon/blade/wandao")->wield();
        carry_object("/clone/cloth/changpao")->wear();
        add_money("silver", 20);
}

