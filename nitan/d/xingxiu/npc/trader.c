// npc: /d/xingxiu/trade.c
// Jay 3/17/96

inherit KNOWER;

void create()
{
        set_name("波斯商人", ({ "bosi shangren", "shangren", "trader" }));
        set("gender", "男性");
        set("age", 40 + random(10));

        set("long", "一個高鼻藍眼的波斯商人。他看着你臉上露出狡猾的笑容。\n");

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
"波斯商人對你擠了一下眼睛。\n",
"波斯商人對你説：阿拉阿可巴，穆罕默德瑞素阿拉。你沒聽懂。\n",
                (: random_move :)
        }) );
        carry_object(__DIR__"obj/wandao")->wield();
        carry_object(__DIR__"obj/changpao")->wear();
        add_money("silver", 20);
}

