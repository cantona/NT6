// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "雷霆一擊" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手使用。\n");

        if ((int)me->query_skill("force") < 250)
                return notify_fail("你內功修為不夠，難以施展" + name() + "。\n");

        if( query("max_neili", me)<2500 )
                return notify_fail("你內力修為不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("dragon-strike", 1) < 180)
                return notify_fail("你降龍十八掌火候不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("strike") != "dragon-strike")
                return notify_fail("你沒有激發降龍十八掌，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "dragon-strike")
                return notify_fail("你沒有準備降龍十八掌，難以施展" + name() + "。\n");

        if( query("neili", me)<600 )
                return notify_fail("你現在真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIC "$N" HIC "默運內功，施展出" + name() + HIC "，全身急速轉動起來，"
              "越來越快，就\n猶如一股旋風，驟然間，$N" HIC "已卷向正看"
              "得發呆的" HIC "$n。\n"NOR;

        ap = attack_power(me, "strike") + me->query_str()*10;
        dp = defense_power(target, "dodge") + target->query_dex()*10;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                damage+= query("jiali", me);
                addn("neili", -400, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 85,
                                           HIR "$p" HIR "只見一陣旋風影中陡然現出$P"
                                           HIR "的雙拳，根本來不及躲避，被重重擊中，\n五"
                                           "髒六腑翻騰不休，口中鮮血如箭般噴出！\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += HIG "可是$p" HIG "看破了$P" HIG "的企圖，沒"
                       "有受到迷惑，閃在了一邊。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
