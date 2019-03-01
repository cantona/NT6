// maque.c

inherit NPC;

void create()
{
        set_name("麻雀", ({ "ma que"}));
        set("race", "飛禽");
        set("age", 3);
        set("long", "一只小麻雀，在石室裡飛上飛下。\n");
        set("attitude", "peaceful");

        set("combat_exp", 300);
        set_temp("apply/attack", 3);
        set_temp("apply/defense", 5);
        set_temp("apply/armor", 1);

        set("chat_chance", 10);
        set("chat_msg", ({
                "麻雀唧唧喳喳叫了幾聲。\n",
                "麻雀撲騰著翅膀。\n",
                "麻雀一下撞到牆上，“碰”地一聲又掉在地上。\n",
        }) );

        setup();
}