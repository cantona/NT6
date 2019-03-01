// Npc: /d/kunlun/npc/xueji.c
// Last Modified by winder on Jun. 29 2001

inherit NPC;

void create()
{
        set_name("雪雞", ({ "xue ji","ji" }) );
        set("race", "飛禽");
        set("age", 2);
        set("long", "一只肥肥白白的雪雞。\n");

        set("combat_exp", 100);
        set_temp("apply/attack", 20);
        set_temp("apply/defense", 20);
        set_temp("apply/damage", 20);
        set_temp("apply/armor", 10);

        setup();
}

void die()
{
       object ob;
       message_vision("$N慘嚎一聲，慢慢倒下死了！\n", this_object());
       ob = new(__DIR__"obj/xueji-rou");
       ob->move(environment(this_object()));
       destruct(this_object());
}
