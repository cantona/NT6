#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "佛光初現" NOR; }

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，無法施展" + name() + "。\n");

        if ((int)me->query_skill("emei-jian", 1) < 60)
                return notify_fail("你的峨嵋劍法不夠嫻熟，無法施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在真氣不夠，無法施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "emei-jian")
                return notify_fail("你沒有激發峨嵋劍法，無法施展" + name() + "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "跨步上前，手中" + weapon->name() +
              HIY "將峨眉劍法運轉如飛，劍光霍霍徑直逼向$n"
              HIY "。\n" NOR;

        addn("neili", -75, me);
        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        me->start_busy(3);
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
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
        return  HIR "頓時只聽“嗤”的一聲，$n" HIR "稍個不慎，"
                "被這一劍劃得鮮血淋漓。\n" NOR;
}
