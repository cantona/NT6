// sanshen.c 華嶽三神峯

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "華嶽三神峯" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, damage;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");

        if( query("max_neili", me)<1800 )
                return notify_fail("你的內力修為不夠，無法施展" + name() + "！\n");

        if( query("neili", me)<320 )
                return notify_fail("你的真氣不夠！\n");

        if ((int)me->query_skill("fanliangyi-dao", 1) < 100)
                return notify_fail("你反兩儀刀法火候不足，無法施展" + name() + "\n");

        if ((int)me->query_skill("force", 1) < 140)
                return notify_fail("你的內功修為不足，無法施展" + name() + "\n");

        if (me->query_skill_mapped("blade") != "fanliangyi-dao")
                return notify_fail("你還沒有激發反兩儀刀法，無法施展" + name() + "！\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "\n$N" HIY "使出華山派絕技「" HIG "華嶽三神峯" HIY "」，身\n"
              "法突然變得異常靈動飄忽！手中" + weapon->name() + HIY "連連卷"
              "向$n" HIY "。" NOR;
        message_combatd(msg, me, target);

        msg = HIW "$N" HIW "反轉" + weapon->name() + HIW "，忽然一刀劈出，威力無窮。\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) < dp)
                msg += CYN "$n" CYN "向外一跳閃過了這招。\n" NOR;
        else
        {
                damage = damage_power(me, "blade");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           HIR "$n" HIR "躲避不及，被$N"
                                           HIR "這刀砍中肩膀，鮮血直流。\n" NOR);
        }

        msg += HIW "\n$N" HIW "迴轉" + weapon->name() + HIW "，猛地大步向前，直襲$n" HIW "下盤。\n" NOR;
        if (ap / 2 + random(ap) < dp)
                msg += CYN "$n" CYN "縱身而起，躲過這一招。\n" NOR;
        else
        {
                damage = damage_power(me, "blade");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           HIR "$n"HIR "閃避不及，大腿已被$N" HIR "砍得血肉模糊！\n" NOR);
        }

        msg += HIW "\n$N" HIW "飛身躍起，手中" + weapon->name() + HIW "自天而下，劈向$n" HIW "。\n" NOR;
        if (ap / 2 + random(ap) < dp)
                msg += CYN "$n" CYN "一快打快，向後飛身一跳，竟躲過這招。\n" NOR;
        else
        {
                damage = damage_power(me, "blade");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "$n" HIR "正猶豫劍，刀光劃過，鮮血已染滿刀身。！\n" NOR);
        }

        me->start_busy(3);
        message_combatd(msg, me, target);
        return 1;
}