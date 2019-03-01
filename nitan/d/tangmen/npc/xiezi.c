// xiezi.c

#include <ansi.h>
inherit NPC;

void create()
{
        set_name("毒蠍子", ({ "duxie", "xiezi" }) );
        set("race", "野獸");
        set("age", 3);
        set("long", "一只紅黃兩色相間的毒蠍子，聽說巨毒無比。\n");
        set("attitude", "peaceful");

        set("limbs", ({ "頭部", "身體", "前螯", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );

        set("combat_exp", 40000);
        set_temp("apply/attack", 5);
        set_temp("apply/defense", 2);
        set_temp("apply/armor", 10);

        setup();
}

int hit_ob(object me, object ob, int damage)
{
//        if ((int)ob->query("combat_exp") > 100000) return 1 ;
        if( query("combat_exp", ob)>100000)return 1;
        if( random(damage)>query_temp("apply/armor", ob) && ob->query_condition("xie_poison")<20 )
        {
                ob->apply_condition("xie_poison", 40);
                tell_object(ob, HIG "你覺得被叮中的地方一陣麻木！\n" NOR );
        }
}

void die()
{
        object ob;
        message_vision("$N尾巴“啪”的一聲折斷，冒出一股汁液，死了。\n", this_object());
//        ob = new(__DIR__"xiezike");
//        ob->move(environment(this_object()));
        destruct(this_object());
}
