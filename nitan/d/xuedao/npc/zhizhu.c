// zhizhu.c

#include <ansi.h>
inherit NPC;
void create()
{
    set_name(HIB"毒蜘蛛"NOR, ({ "du zhizhu" }));
    set("long", "一隻有毒蜘蛛。\n");

    set("race", "昆蟲");
        set("subrace", "爬蟲");
    set("age", 3);
    set("attitude", "peaceful");

    set("max_ging", 80);
    set("max_qi", 80);
    set("str", 10);
    set("cor", 50);

    set("limbs", ({ "嘴","觸角", "身體", "尾刺"}));
    set("verbs", ({ "bite" }) );

    set_temp("apply/attack", 10);
    set_temp("apply/damage", 10);
    set_temp("apply/armor", 10);

    set("combat_exp", 1000);
    setup();
}

int hit_ob(object me, object ob, int damage)
{
        if( random(damage)>query_temp("apply/armor", ob) && 
            ob->affect_by("poison", ([ "level" : random(10) + 10,
                                       "name"  : "蛛毒",
                                       "id"    : "nature poison",
                                       "duration" : 5 + random(10), ])))
        {
                tell_object(ob, HIG "你感到身體變得冰涼！\n" NOR );
        }
}
