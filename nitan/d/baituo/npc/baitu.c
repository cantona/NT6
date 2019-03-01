//baitu.c
inherit NPC;

void create()
{
        set_name("白兔", ({ "bai tu", "tu" }) );
        set("race", "野獸");
        set("age", 2);
        set("long", "一隻雪白的小白兔，可愛之致。\n");
        set("attitude", "peaceful");
 
        set("str", 15);
        set("cor", 16);

        set("limbs", ({ "頭部", "身體", "爪子", "尾巴" }) );
        set("verbs", ({ "bite" }) );
 
        set("combat_exp", 200);

        set_temp("apply/attack", 5);
        set_temp("apply/damage", 3);
        set_temp("apply/defence",5);
        set_temp("apply/armor",2);

        setup();
}

void die()
{
        object ob;
        message_vision("$N兩腿一蹬，$N死了。\n", this_object());
        ob = new("/d/baituo/obj/turou");
        ob->move(environment(this_object()));
        destruct(this_object());
}