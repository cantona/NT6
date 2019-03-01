// wuya.c
// Last Modified by winder on Aug. 1 2002

inherit NPC;

void create()
{
        set_name("烏鴉", ({ "wuya", "crow" }) );
        set("race", "飛禽");
        set("age", 3);
        set("long", "一只黑色的烏鴉，醜陋極了。\n");
        set("attitude", "peaceful");

        set("combat_exp", 300);
        set_temp("apply/attack", 3);
        set_temp("apply/defense", 5);
        set_temp("apply/armor", 1);

        setup();

        set("chat_chance", 10);
        set("chat_msg", ({
                "烏鴉「嘎嘎」叫了幾聲。\n",
                "烏鴉叫道：「嘎嘎」。\n",
                "烏鴉在你眼前飛上飛下。\n",
        }) );
}