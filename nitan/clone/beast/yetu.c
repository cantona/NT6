// Code of ShenZhou
// yetu.c 野兔

inherit NPC;

void create()
{
        set_name("野兔", ({ "ye tu", "ye", "hare" }) );
        set("race", "家畜");
        set("age", 5);
        set("long", "一只好可愛的小野兔。\n");
        set("attitude", "peaceful");
        
//        set("limbs", ({ "頭部", "身體", "前腳", "後腳", "尾巴" }) );
//        set("verbs", ({ "bite", "claw" }) );

        set("combat_exp", 50);
//        set("shen_type", 0);

//        set("chat_chance", 6);
//        set("chat_msg", ({
//                (: this_object(), "random_move" :),
//        }) );
        
        set_temp("apply/attack", 2);
        set_temp("apply/defense", 5);
        set_temp("apply/damage", 2);
        set_temp("apply/armor", 1);

        setup();
}

void die()
{
        object ob;
        message_vision("$N凄慘的嚎了幾聲，死了。\n", this_object());
        ob = new(__DIR__"turou");
        ob->move(environment(this_object()));
        destruct(this_object());
}
        