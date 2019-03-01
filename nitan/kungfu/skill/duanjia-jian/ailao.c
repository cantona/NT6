// ailao.c 哀牢山劍意

#include <ansi.h>

inherit F_SSERVER;

string name() { return "哀牢山劍意"; }

int perform(object me, object target)
{
        object weapon;
        int i, a;

        if (!target) target=offensive_target(me);

        if (!target
                || !target->is_character()
                || !me->is_fighting(target))
                return notify_fail("你不在戰鬥中！\n");

//      if (target->is_busy())
//              return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧□\n");

        weapon=query_temp("weapon", me);
        if( !objectp(weapon) || query("skill_type", weapon) != "sword" )
                return notify_fail("你手中無劍，如何使得出哀牢山劍意？\n");

        if (me->query_skill("kurong-changong", 1)<150)
                return notify_fail("你的內功火候未到，無法駕馭哀牢山劍意！\n");

        if (me->query_skill("sword", 1) < 150)
                return notify_fail("你劍法修為不夠，無法施展哀牢山劍意！\n");

        if (me->query_skill("duanjia-jian",1)<150)
                return notify_fail("你段家劍修為不夠，無法施展哀牢山劍意！\n");

        if( me->query_skill_mapped("force") != "kurong-changong")
                return notify_fail("你所用的內功與哀牢山劍意氣路相悖！\n");

        if( query("neili", me) <= 500 )
                return notify_fail("你的內力不夠使用哀牢山劍意！\n");

        message_vision(HIR "\n突然間$N劍法突變，劍氣縱橫，上六劍，下六劍，前六劍，後六劍，左六劍，\n\n"NOR, me, target);
        message_vision(HIR "\n右六劍，施展哀牢山劍意對$n虛虛實實連刺了三十六劍！\n\n" NOR, me, target);

        if( query("combat_exp", me)*10/query("combat_exp", target)<12 )
                a=3;
        else {
                if( query("combat_exp", me)*10/query("combat_exp", target)<15 )
                        a=4;
                else {
                        if( query("combat_exp", me)*10/query("combat_exp", target)<18 )
                                a=5;
                        else a=6;
                }
        }

        for (i=1; i<=a; i++)
                COMBAT_D->do_attack(me, target, weapon);


        if (a>4)
        {
                me->start_busy(a-random(3));
        } else
                me->start_busy(1);

        addn("neili", -200, me);
        addn("jing", -20, me);
        return 1;
}