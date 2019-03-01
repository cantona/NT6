// wushuang.c 玉女劍法 無雙無對

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "無雙無對"; }

void remove_effect(object me, int a_amount, int d_amount);

int perform(object me, object target)
{
        object weapon;
        int damage;
        int skill;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("無雙無對只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if ((int)me->query_skill("yunu-sword", 1) < 80)
                return notify_fail("你的玉女劍法不夠嫻熟，不會使用「無雙無對」。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功不夠嫻熟，不會使用「無雙無對」。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的內力不夠。\n");

        if( query_temp("hsj_wu", me) )
                return notify_fail("你已經在運功中了。\n");

        msg = HIY "$N" HIY "雙手握起" + weapon->name() + HIY
              "，劍芒暴長，一式「無雙無對」，馭劍猛烈絕倫地往$n"
              HIY "沖刺！\n"NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);

                damage = damage_power(me, "sword");
                addn("neili", -250, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           HIR "$n" HIR "看到$N" HIR "這一劍妙到毫巔，全然無"
                                           "法抵擋，一愣神之間已經被這一劍刺得鮮血飛濺！" NOR);
        } else
        {
                me->start_busy(3);
                msg += CYN "可是$p" CYN "看破了$P"
                       CYN "的企圖，向旁一躍，躲了開去。" NOR;
        }

        message_combatd(msg, me, target);
        return 1;
}
