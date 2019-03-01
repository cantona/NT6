inherit NPC;

void create()
{
        set_name("魚怪", ({ "fish monster", "fish" }) );
        set("race", "野獸");
        set("age", 300);
        set("long", "這是一只身形很大，已成精怪的魚，渾身覆滿絢麗的鱗片，\n"
            "一口鋒利的牙齒，正虎視耽耽的看著你\n");
        set("attitude", "aggressive");

        set("max_qi",10000); 
        set("max_jing",10000);
        set("max_neili",10000);
        set("str", 26);
        set("cor", 30); 
        set("dex", 30);
        set("limbs", ({ "頭部", "身體", "腹部", "尾巴" }) );

        set("verbs", ({ "bite" }) );

        set("combat_exp", 500000);
        
        set_temp("apply/attack", 300);
        set_temp("apply/damage", 300);
        set_temp("armor", 800);
        setup();
}

void die()
{
        object ob;
        message_vision("$N口中吐出一粒內丹，肚皮往上一翻，$N死了。\n", this_object());
        ob = new("/quest/tulong/obj/neidan");
        ob->move(environment(this_object()));
        destruct(this_object());
}
