// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "噬血穹蒼" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage;
        int i, count;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 250)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("xuedao-daofa", 1) < 180)
                return notify_fail("你的血刀大法還不到家，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "xuedao-daofa")
                return notify_fail("你沒有激發血刀大法為刀法，難以施展" + name() + "。\n");

        if( query("qi", me)<100 )
                return notify_fail("你目前氣血翻滾，難以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你目前真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        ap = attack_power(me, "blade") + me->query_str() * 20;
        dp = defense_power(target, "dodge") + target->query_dex() * 20;

        msg = HIY "$N" HIY "陡然施出「" HIR "噬血穹蒼" HIY "」，手中" +
              weapon->name() + HIY "騰起無邊殺意，攜著風雷之勢向$n" HIY
              "劈斬而去！\n"NOR;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 75,
                                           HIR "$n" HIR "只覺眼前一蓬血雨噴洒而出"
                                           "，已被$N" HIR "這一刀劈了個正中。\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "只見$P" CYN "來勢洶湧，難以抵擋，當"
                       "即飛身朝後躍出數尺。\n" NOR;
        }

        msg += HIY "\n緊接著$N" HIY "嗔目大喝，手中" + weapon->name() +
               HIY "一振，迸出漫天血光，舖天蓋地洒向$n" HIY "！\n"NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");
        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "霎時間$n" HIR "只覺周圍殺氣彌漫，全身氣血翻"
                       "滾，甚難招架。\n" NOR;
                count = ap / 10;
        } else
        {
                msg += HIY "霎時間$n" HIY "只覺周圍殺氣彌漫，心底微微一"
                       "驚，連忙奮力招架。\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        addn_temp("apply/attack", count, me);
        addn_temp("apply/damage", count, me);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count, me);
        me->start_busy(1 + random(3));
        addn("neili", -200-random(300), me);
        return 1;
}
