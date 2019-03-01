// lbee.c

inherit NPC;

void create()
{
        set_name("小蜜蜂", ({ "little bee", "bee"}) );
        set("race", "野獸");
        set("age", 2);
        set("long", "一隻飛來飛去的小蜜蜂。\n");
        
        set("str", 30);
        set("dex", 40);

        set("limbs", ({ "頭部", "身體", "翅膀", "尾巴" }) );
        set("verbs", ({ "bite", "poke" }) );

        set_temp("apply/attack", 10);
        set_temp("apply/armor", 3);
        
        set("chat_chance", 2);
        set("chat_msg", ({
                (: this_object(), "random_move" :),
        "小蜜蜂嗡嗡嗡飛過來，在你頭上轉了一圈，又飛走了。\n",
         }) );

        setup();
}
