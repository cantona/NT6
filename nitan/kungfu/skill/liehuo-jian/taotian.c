// taotian.c 烈火劍法

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "烈燄滔天"; }

int perform(object me, object target)
{
        object weapon;
        int ap, dp, damage;
        string msg;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail("「烈燄滔天」只能對戰鬥中的對手使用。\n");

        if (! objectp(weapon = query_temp("weapon", me)) ||
            (string)query("skill_type", weapon) != "sword")
                return notify_fail("你使用的武器不對。\n");

        if ((int)me->query_skill("liehuo-jian", 1) < 70)
                return notify_fail("你的烈火劍法不夠嫻熟，不會使用「烈燄滔天」。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功修為不夠高。\n");

        if ((int)query("neili", me) < 300)
                return notify_fail("你現在真氣不夠，不能使用「烈燄滔天」。\n");

        if (me->query_skill_mapped("sword") != "liehuo-jian")
                return notify_fail("你現在沒有激發烈火劍法，不能使用「烈燄滔天」。\n");

        msg = HIR "$N" HIR "口中暴喝一聲：熊熊烈火，焚我殘軀，生亦何歡，死亦何苦！\n\n"
              "剎那間渾身上下火光沖天，滾滾熱浪帶起強大的氣流四處沖擊！\n\n"
              "$N" HIR "冷笑下，騰身而起，人與" + weapon->name() + HIR "合而為一，直向$n" HIR "撲去，氣勢驚人！\n\n"NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                damage = damage_power(me, "sword");
                addn("neili", -200, me);
                me->receive_wound("qi",random(damage/3));
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           HIR "只見$N" HIR "渾身的火光將$n"
                                           HIR "團團圍住，$n" HIR "的慘呼聲"
                                           "令人毛骨悚然！\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += HIC "可是$p" HIC "猛地向邊上一躍，跳出了$P" HIC "的攻擊范圍。\n"NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}