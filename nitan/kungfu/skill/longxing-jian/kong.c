#include <ansi.h>
#include <combat.h>

#define ZHUAN "「" HIY "金龍疾空" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, attack_time;

        if( userp(me) && !query("can_perform/longxing-jian/kong", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHUAN "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" ZHUAN "。\n");

        if ((int)me->query_skill("longxing-jian", 1) < 160)
                return notify_fail("你的龍形劍法不夠嫻熟，難以施展" ZHUAN "。\n");

        if( query("neili", me)<250 )
                return notify_fail("你的真氣不夠，難以施展" ZHUAN "。\n");

        if (me->query_skill_mapped("sword") != "longxing-jian")
                return notify_fail("你沒有激發龍形劍法，難以施展" ZHUAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "一聲清嘯，手中" + weapon->name() +
              HIY "龍吟不定，劃向虛空，剎那間，一道金光疾射，"
              HIY "猶如一條金龍騰越在半空，猛地射向$n" HIY "。\n" NOR;

        ap = me->query_skill("sword");
        dp = target->query_skill("parry");
        attack_time = 7;
        if (ap / 2 + random(ap * 2) > dp)
        {
                msg += HIR "結果$p" HIR "被$P" HIR
                       "攻了個措手不及，連連後退不暇！\n" NOR;
                count = ap / 6;
                attack_time += random(ap / 45);
        } else
        {
                msg += HIC "$n" HIC "見$N" HIC "這幾劍並無破綻"
                       "，不敢大意，小心應付。\n" NOR;
                count = 0;
        }
                
        message_combatd(msg, me, target);

        if (attack_time > 10)
                attack_time = 10;

        addn("neili", -attack_time*20, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(1 + random(attack_time));

        return 1;
}