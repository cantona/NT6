#include <ansi.h>
#include <combat.h>

string name() { return HIW "雪花六出" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, attack_time;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的內功的修為不夠，難以施展" + name() + "。\n");

        if (me->query_skill("xueshan-jian", 1) < 140)
                return notify_fail("你的雪山劍法修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "xueshan-jian")
                return notify_fail("你沒有激發雪山劍法，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        /*
        msg = HIW "$N" HIW "手中" + weapon->name() + HIW
              "抖動，正是一招「雪花六出」。虛中有實，實中有"
              "虛，四面八方向$n" HIW "攻去！\n" NOR;
        */
        msg = HIY"$N一抖手中" + weapon->name() + HIY"，一式"HIW"「雪花六出」"HIY"，連續刺出六劍，劍劍快如流星，\n"
              "幻成雪花六點，帶起一陣寒□向前疾飄而去。\n"NOR;
        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");
        attack_time = 6;

        if (ap / 2 + random(ap * 2) > dp)
        {
                msg += HIR "$n" HIR "只覺劍影重重，登時眼花繚"
                       "亂，被攻了個措手不及，疲于奔命。\n" NOR;
                count = ap / 10;
                addn_temp("apply/attack", count, me);
        } else
        {
                msg += HIC "$n" HIC "見$N" HIC "劍招洶湧，寒"
                       "風襲體，急忙凝神聚氣，小心應付。\n"
                       NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        addn("neili", -attack_time*20, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(3));
        return 1;
}