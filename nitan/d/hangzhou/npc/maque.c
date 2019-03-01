// maque.c
// Last Modified by winder on Aug. 1 2002

inherit NPC;

void create()
{
        set_name("麻雀", ({ "maque"}));
        set("race", "飛禽");
        set("age", 3);
        set("long", "一隻小麻雀，在樹枝間跳上跳下。\n");
        set("attitude", "peaceful");

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
