#include <ansi.h>
inherit KNOWER;

void create()
{
        set_name("波斯商人", ({ "bosi shangren", "shangren", "bosi" }));
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
                CYN "波斯商人對你擠了一下眼睛。\n" NOR,
                CYN "波斯商人對你説：阿拉阿可巴，穆罕默德瑞素阿拉。\n" NOR,
                CYN "波斯商人呵呵笑了笑，神祕兮兮的看着你：。\n" NOR,
                (: random_move :)
        }) );
        carry_object("/clone/weapon/wandao")->wield();
        carry_object("/clone/cloth/changpao")->wear();
        add_money("silver", 20);
}