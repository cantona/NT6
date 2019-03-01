#include <ansi.h>
inherit F_SSERVER;

string name() { return "刀影掌"; }

int perform(object me,object target)
{
        int j = me->query_skill("murong-daofa", 1);
        object weapon=query_temp("weapon", me);

        if( !target ) target = offensive_target(me);
        j = j * 2 / 3;
        if( !target || !me->is_fighting(target) )
                return notify_fail("刀影掌只能對戰鬥中的對手使用。\n");

        if( (int)me->query_skill("shenyuan-gong", 1) < 100 )
                return notify_fail("你的內功還未練成，不能使用刀影掌！\n");

        if( (int)me->query_skill("murong-daofa", 1) < 100 )
                return notify_fail("你的刀法還未練成，不能使用刀影掌！\n");

        if( !weapon || query("skill_type", weapon) != "blade"
        || me->query_skill_mapped("blade") != "murong-daofa")
                return notify_fail("你手裡沒有刀，無法使用刀影掌！\n");

        if((int)me->query_skill("xingyi-zhang", 1) < 100 )
                return notify_fail("你的掌法還未練成，不能使用刀影掌！\n");

        if(me->query_skill_mapped("force") != "shenyuan-gong")
                return notify_fail("你的內功不是神元功，無法使用刀影掌！\n");

        if(me->query_skill_mapped("strike") != "xingyi-zhang" ||
           me->query_skill_prepared("strike") != "xingyi-zhang")
                return notify_fail("你沒有用掌，無法使用刀影掌！\n");

        if(me->query_skill_mapped("parry") != "xingyi-zhang")
                if(me->query_skill_mapped("parry") != "murong-daofa")
                       return notify_fail("你的招架功夫不對，無法使用刀影掌！\n");

        if( query("max_neili", me)<1200 )
                return notify_fail("你現在內力修為不夠，不能使用刀影掌！\n");

        if( query("neili", me)<600 )
                return notify_fail("你現在內力不足，不能使用刀影掌！\n");

        if((int)me->query_skill("blade", 1) < 100 )
                return notify_fail("你的基本刀法不夠嫻熟，不能在刀招中夾雜使用刀影掌。\n");

        if((int)me->query_skill("strike", 1) < 100 )
                return notify_fail("你的基本掌法不夠嫻熟，不能在刀招中夾雜使用刀影掌。\n");

        message_combatd(HIR"\n$N大吼一聲使出慕容絕技「刀影掌」，只見$P掌隨刀走，片片刀光中夾雜著陣陣掌風一起奔向$n！\n"NOR, me,target);
        addn("neili", -200, me);
        addn_temp("apply/attack", j, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);
        weapon->unequip();
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);
        weapon->wield();
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);
        if ((int)me->query_str() > 30)
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);
        addn_temp("apply/attack", -j, me);
        me->start_busy(2+random(2));
        return 1;
}
