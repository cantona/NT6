//bee.c

inherit NPC;

void create()
{
        set_name("蜜蜂", ({"bee"}) );
        set("race", "昆蟲");
       set("subrace", "飛蟲");
        set("age", 8);
        set("long", "這是一只蜜蜂，正忙著採蜜。\n");
        
        set("str", 40);
        set("dex", 50);

        set("limbs", ({ "頭部", "身體", "翅膀", "尾刺" }) );
        set("verbs", ({ "bite", "poke" }) );

        set_temp("apply/attack", 33);
        set_temp("apply/armor", 20);
        
        set("chat_chance", 2);
        set("chat_msg", ({
                (: this_object(), "random_move" :),
        "蜜蜂嗡嗡嗡飛過來，在你頭上轉了一圈，有飛走了。\n",
         }) );

        setup();
}

