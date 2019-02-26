// Npc: /d/kunlun/npc/sheep.c
// Last Modified by winder on Jun. 29 2001

inherit NPC;

void create()
{
        set_name("野山羊", ({ "shan yang", "sheep" }) );
        set("race", "走畜");
        set("age", 5);
        set("long","一隻温順可愛的野山羊。它正在低頭吃草，見了人也不驚避。\n");

        set("combat_exp", 100);
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 30);
        set_temp("apply/damage", 30);
        set_temp("apply/armor", 10);

        setup();
}
void die()
{
       object ob;
       message_vision("$N慘嚎一聲，慢慢倒下死了！\n", this_object());
       ob = new(__DIR__"obj/yang-rou");
       ob->move(environment(this_object()));
       destruct(this_object());
}
