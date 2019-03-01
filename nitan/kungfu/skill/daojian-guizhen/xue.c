// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "天下有" HIR "血" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string type, msg;
        object weapon, weapon2;
        int i, count, damage;
        int ap, dp;

        if (me->query_skill("daojian-guizhen", 1) < 200)
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword"
            && query("skill_type", weapon) != "blade" )
                return notify_fail("你所使用的武器不對，難以施展" + name() + "。\n");

        type=query("skill_type", weapon);

        if (me->query_skill(type, 1) < 250)
                return notify_fail("你的" + to_chinese(type) + "太差，"
                                   "難以施展" + name() + "。\n");

        if (me->query_skill_mapped(type) != "daojian-guizhen")
                return notify_fail("你沒有激發刀劍歸真，難以施展" + name() + "。\n");

        if (me->query_skill("daojian-guizhen", 1) < 250)
                return notify_fail("你的劍歸真等級不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N" HIW "手中" + weapon->name() + HIW "驀地一抖"
              "，將「" NOR + WHT "胡家刀法" HIW "」並「" NOR + WHT
              "苗家劍法" HIW "」連環施出。霎時寒\n光點點，猶如夜隕"
              "劃空，舖天蓋地罩向$n" HIW "，正是一招「" HIW "天下"
              "有" HIR "血" HIW "」。\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIW "$n" HIW "只見無數刀光劍影向自己逼"
                       "來，頓感眼花繚亂，心底寒意油然而生。\n" NOR;
                count = ap / 15;
                set_temp("daojian-guizhen/max_pfm", 1, me);
        } else
        {
                msg += HIG "$n" HIG "突然發現自己四周皆被刀光"
                       "劍影所包圍，心知不妙，急忙小心招架。\n" NOR;
                count = ap / 30;
        }
        message_combatd(msg, me, target);

        addn("neili", -300, me);
        addn_temp("apply/attack", count, me);
        addn_temp("apply/damage", count*2/3, me);

        for (i = 0; i < 12; i++)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me, target, weapon, 100);
        }
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count*2/3, me);
        delete_temp("daojian-guizhen/max_pfm", me);
        me->start_busy(2 + random(2));
        return 1;
}
