#include <ansi.h>
#include <combat.h>

string name() { return HIY "傲塵劍" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+ "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不對，難以施展" +name()+ "。\n");

        if ((int)me->query_skill("pichen-jian", 1) < 100)
                return notify_fail("你辟塵劍法不夠嫻熟，難以施展" +name()+ "。\n");

        if (me->query_skill_mapped("sword") != "pichen-jian")
                return notify_fail("你沒有激發辟塵劍法，難以施展" +name()+ "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不足，難以施展" +name()+ "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "一陣狂笑，激得周圍塵砂飛揚，手中" + weapon->name() +
              HIY "攜著排山倒海之勢朝$n" HIY "劈去。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -150, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                                           HIR "$n" HIR "招架不利，只覺劍光閃過，"
                                           "隨覺胸口一陣劇痛，噴出一口鮮血。\n" NOR);
        } else
        {
                addn("neili", -50, me);
                me->start_busy(3);
                msg += CYN "可是" CYN "$n" CYN "早有防備，飛身一躍"
                       "而起，避開了$N" CYN "的劍招。\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
