#include <ansi.h>
#include <combat.h>

string name() { return HIR "騰訣" NOR; }

inherit F_SSERVER;

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

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("longteng-daofa", 1) < 140)
                return notify_fail("你的龍騰刀法還不到家，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "longteng-daofa")
                return notify_fail("你沒有激發龍騰刀法，難以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIR "$N" HIR "嘴角泛起邪意的微笑，猛地加速前衝，左手" + weapon->name() +
              HIR "化作一道白虹，\n頓時一股凌厲無比的無形刀氣破空襲向$n" HIR "！\n"NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                addn("neili", -150, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70,
                                           HIR "只見$n" HIR "一聲慘叫，整個人如遭"
                                           "電擊，刀氣穿心，口中鮮血狂噴而出！\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += CYN "可是$p" CYN "默運內力，硬是抵擋了$P"
                       CYN "的這記無形刀氣。\n"NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
