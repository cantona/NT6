#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "雄霸羣山" NOR; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

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

        if ((int)me->query_skill("force") < 60)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("chuangwang-dao", 1) < 40)
                return notify_fail("你的闖王刀法還不到家，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "chuangwang-dao")
                return notify_fail("你沒有激發闖王刀法，難以施展" + name() + "。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "$N" HIY "一聲怒喝，手中" + weapon->name() +  HIY "凌空劈斬"
              "而出，刀鋒頓時如閃電般貫向$n" HIY "！\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                addn("neili", -30, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 25,
                                           HIR "$n" HIR "稍作遲疑，不想被$N" HIR
                                           "一刀劈中，頓時一聲慘呼，血濺五步！\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += CYN "可是$p" CYN "微微一笑，身子朝一旁偏過尺許，躲開$P"
                       CYN "這一刀。\n" NOR;
                addn("neili", -10, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}