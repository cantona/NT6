// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "劍芒" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage;
        object ob;

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

        if ((int)me->query_skill("zhougong-jian", 1) < 140)
                return notify_fail("你的周公劍火候太淺，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的內功修為太淺，難以施展" + name() + "。\n");

        if( query("max_neili", me)<2200 )
                return notify_fail("你的內力修為太淺，難以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在的真氣不足，，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        damage = damage_power(me, "sword");

        msg = HIW "$N" HIW "一聲清嘯，手中" + weapon->name() + HIW "凌"
                  "空劃出，劍尖陡然生出半尺吞吐不定的青芒，一道劍氣破空"
                  "徑直劃向$n。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 85,
                                           HIR "$n" HIR "一聲慘叫，凌厲的劍氣已劃"
                                           "過氣門，在身上刺出數個血洞，鮮血如泉"
                                           "水般湧出！\n" NOR);
        } else
        {
                msg += CYN "可是$n" CYN "看破了$N"
                       CYN "的企圖，斜躍避開。\n" NOR;
        }

        msg += HIW "\n$N" HIW "見$n" HIW "應接不暇，一聲冷笑，兵刃揮洒而"
              "出，一記更加凌厲的劍芒由劍尖彈射而出，凌空直射$n" HIW
              "。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90,
                                           HIR "只聽“噗嗤”一聲，劍氣正中$n" HIR
                                           "胸口，留下一個碗口大的血洞！$n" HIR
                                           "哀嚎一聲，再也無法站起。\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "強忍全身的痛楚，飛身一躍，避開了$N"
                       CYN "這強大的殺著。\n" NOR;
        }
        me->start_busy(2 + random(2));
        addn("neili", -400, me);
        message_combatd(msg, me, target);
        return 1;
}
