// yang.c 綿羊
// Last Modified by winder on Aug. 1 2002

inherit NPC;

void create()
{
        set_name("綿羊", ({ "mian yang", "yang", "sheep" }) );
        set("race", "走畜");
        set("age", 6);
        set("long", "一頭溫順的小綿羊。\n");
        set("attitude", "peaceful");
        
        set("str", 16);
        set("dex", 15);

        set("combat_exp", 100);

        set_temp("apply/attack", 8);
        set_temp("apply/defense", 10);
        set_temp("apply/damage", 4);
        set_temp("apply/armor", 2);

        setup();
}

void die()
{
        object ob;
        message_vision("$N凄慘的嚎了幾聲，倒在地上死了。\n", this_object());
        ob = new(__DIR__"obj/yangrou2");
        ob->move(environment(this_object()));
        destruct(this_object());
}
