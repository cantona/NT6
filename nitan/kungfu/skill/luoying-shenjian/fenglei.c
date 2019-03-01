// This program is a part of NITAN MudLIB
// fenglei.c

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "風雷四神劍"; }

int perform(object me, object target)
{
        string msg, msg1;
        int i, count;
        object weapon;

        if (! target) target = offensive_target(me);
        if (! target || ! me->is_fighting(target))
                return notify_fail("「風雷四神劍」只能在戰鬥中對對手使用。\n");

        weapon=query_temp("weapon", me);
        if( !weapon || query("skill_type", weapon) != "sword"
        ||  me->query_skill_mapped("sword") != "luoying-shenjian")
                return notify_fail("你必須使用在劍時才能使出「風雷四神劍」！\n");

        if ((int)me->query_skill("luoying-shenjian", 1) < 80)
                return notify_fail("你的落英神劍不夠嫻熟，不會使用「風雷四神劍」。\n");

        if ((int)me->query_skill("bibo-shengong", 1) < 60)
                return notify_fail("你的碧波神功修為不夠，不能使用「風雷四神劍」。\n");

        if ((int)me->query_dex() < 30)
                return notify_fail("你的身法太低，不能使用「風雷四神劍」。\n");

        if (me->query_skill_mapped("force") != "bibo-shengong")
                return notify_fail("你使用的內功不對，不能使用「風雷四神劍」。\n");

        if( query("neili", me)<400 )
                return notify_fail("你現在內力太弱，不能使用「風雷四神劍」。\n");

        i = (me->query_skill("luoying-shenjian", 1) / 4);

        msg = HIG "$N高聲長吟：“桃花影裡飛神劍”，如風如雷般的發出數劍! \n" NOR;

        count = attack_power(me, "sword")/10;
        addn_temp("apply/damage", count, me);
        addn_temp("apply/str", count/10, me);
        addn_temp("apply/attack", count, me);
        message_combatd(msg, me, target);

        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);
        message_combatd(WHT"                                                                           風字訣\n"NOR,me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);
        message_combatd(HIC"                                                                           雨字訣\n"NOR,me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);
        message_combatd(MAG"                                                                           雷字訣\n"NOR,me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);
        message_combatd(HIR"                                                                           電字訣\n"NOR,me);
        addn("neili", -200, me);

        me->start_busy(2);
        addn_temp("apply/damage", -count, me);
        addn_temp("apply/str", -count/10, me);
        addn_temp("apply/attack", -count, me);

        return 1;
}
