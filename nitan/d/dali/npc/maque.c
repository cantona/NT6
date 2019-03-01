// maque.c

inherit NPC;

void create()
{
        set_name("麻雀", ({ "maque"}));
        set("race", "飛禽");
        set("age", 3);
        set("long", "一隻嘰嘰喳喳，飛來飛去的小麻雀。\n");
        set("attitude", "peaceful");

        set("limbs", ({ "頭部", "身體", "翅膀", "爪子", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );

        set("combat_exp", 300);
        set_temp("apply/attack", 3);
        set_temp("apply/defense", 5);
        set_temp("apply/armor", 1);

        set("chat_chance", 10);
        set("chat_msg", ({
        "麻雀在你頭上打個轉，又飛回樹上。\n",
        "麻雀唧唧喳喳叫了幾聲。\n",
        }) );

        setup();
}
