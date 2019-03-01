//hudie.c

inherit NPC;

void create()
{
        set_name("蝴蝶", ({"hudie"}) );
        set("race", "昆蟲");
        set("subrace", "飛蟲");
        set("age", 8);
        set("long", "這是一隻在花間翩翩飛舞的蝴蝶，似乎不怕人呢。\n");

        set("str", 20);
        set("dex", 50);

        set("limbs", ({ "頭部", "身體", "翅膀", "尾巴" }) );
        set("verbs", ({ "bite", "poke" }) );

        set_temp("apply/attack", 33);
        set_temp("apply/armor", 20);

        set("chat_chance", 5);
        set("chat_msg", ({
                (: this_object(), "random_move" :),
        "蝴蝶飛過來，繞着你的身體飛舞起來。等你伸出手來想抓住它時，它又飛走了。\n",
         }) );

        setup();
}

