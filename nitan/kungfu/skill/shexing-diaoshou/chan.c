// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "纏身決" NOR; }

int perform(object me, object target)
{
        int lvl;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+"只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name()+"只能空手使用。\n");

        if( query_temp("gb_chanshen", target) )
                return notify_fail("對方已經被你使"+name()+"纏住了！\n");

        if (target->is_busy())
                return notify_fail("對方正在忙亂中，放心大膽攻擊吧！\n");

        if ((int)me->query_skill("xiaoyaoyou", 1) < 150)
                return notify_fail("你的逍遙遊不夠嫻熟，不能使出"+name()+"！\n");

        if ((int)me->query_skill("shexing-diaoshou", 1) < 150)
                return notify_fail("你的蛇行刁手不夠嫻熟，不能使出"+name()+"！\n");

        if ((int)me->query_skill("huntian-qigong", 1) < 150)
                return notify_fail("你的混天氣功等級不夠，不能使出"+name()+"！\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力太弱，不能使出"+name()+"！\n");

        if( query("neili", me)<200 )
                return notify_fail("你的內力太少了，不能使出"+name()+"！\n");

        /*
        if( !query_temp("gb_huixuan", me) )
                return notify_fail("你沒有使出逍遙迴旋步，無法使出纏身決！\n");
        */

        lvl = ((int)me->query_skill("xiaoyaoyou", 1) +
               (int)me->query_skill("shexing-diaoshou", 1)) / 2;

        message_combatd(HIB "\n突然間$N口中發出“嘶嘶”的聲音，雙手半曲，三指上豎成蛇狀，\n"
                        "陪合着瀟遙步法，突然欺近$n的身邊，令$n大吃一驚。\n" NOR, me, target);

        addn("neili", -100+random(50), me);

        addn_temp("apply/defense", -lvl/3, target);
        addn_temp("apply/armor", -lvl/3, target);

        ap = attack_power(me, "hand");
        dp = defense_power(target, "dodge");
        if( ap / 2 + random(ap) > dp )
        {
                message_combatd(HIB "但見$N的身形有如蛇蠍纏身一般，環在$n的身邊，令$n不知所措，\n"
                                "只覺的仿拂有無形的繩索慢慢的束縛了$n。\n" NOR, me, target);

                target->start_busy(3 + random(lvl / 120));
        }

        set_temp("gb_chanshen", 1, target);
        me->start_call_out( (: call_other, __FILE__, "remove_effect", target, lvl / 3 :), lvl / 25);

        return 1;
}

void remove_effect(object target,int lvl)
{
        if (! target) return;

        addn_temp("apply/defense", lvl, target);
        addn_temp("apply/armor", lvl, target);
        delete_temp("gb_chanshen", target);
        if (target->is_fighting())
        {
                // target->start_busy(1 + random(1));
                message_combatd(HIG "$N使出渾身解數，算是掙脱了蛇形刁手的詭異怪招。\n" NOR, target);
        }
}
