#include <ansi.h>
#include <combat.h>

string name() { return HIY "赤燄暴長" NOR; }

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon, weapon2;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對，無法施展" + name() + "。\n");

        if ((int)me->query_skill("jinwu-blade", 1) < 120)
                return notify_fail("你的金烏刀法不夠嫻熟，無法施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在真氣不夠，無法施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "jinwu-blade")
                return notify_fail("你沒有激發金烏刀法，無法施展" + name() + "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "凝神聚氣，將全身之力注入" + weapon->name() +
              HIY "刀身順勢劈下，頓時一股凌厲的刀芒直貫$n" HIY "而去。\n"
              NOR;

        addn("neili", -150, me);
        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if( objectp(weapon2=query_temp("weapon", target) )
            && query("skill_type", weapon2) == "sword"
           && target->query_skill_mapped("sword") == "xueshan-jian")
        {
                msg += HIY "$n" HIY "慌忙中忙以雪山劍法作出抵擋，哪知$N"
                       HIY "刀法竟似雪山劍法克星般，" + weapon->name() +
                       HIY "燄芒霎時\n又暴漲數倍，完全封鎖$n" HIY "的所"
                       "有劍招！\n" NOR;
                ap += ap / 2;
        }

        me->start_busy(2);
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           (: final, me, target, damage :));
        } else
        {
                msg += HIC "可$n" HIC "卻是鎮定逾恆，一絲不亂，"
                       "全神將此招化解開來。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        return  HIR "只聽$n" HIR "一聲慘叫，被這一刀劈個正中，傷口"
                "深可見骨，鮮血四處飛濺。\n" NOR;
}
