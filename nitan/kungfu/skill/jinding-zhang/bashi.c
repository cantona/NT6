// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "八式合一" NOR; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int count,d_count,qi, maxqi, skill;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的內力還不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功的修為不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("jinding-zhang", 1) < 100)
                return notify_fail("你的金頂綿掌的修習不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("strike") != "jinding-zhang")
                return notify_fail("你沒有激發金頂綿掌，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "jinding-zhang")
                return notify_fail("你現在沒有準備使用金頂綿掌，難以施展" + name() + "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "$N" HIY "深深吸了一口氣，提起全身的功力於"
              "雙掌猛力拍出，只聽得骨骼一陣爆響！\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                damage += (int)me->query_skill("linji-zhuang", 1);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "只見漫天掌影飄忽不定的罩向$n" HIR
                                           "全身各個部位，$n" HIR "頓時接連中了數"
                                           "掌！\n" NOR);
                addn("neili", -100, me);
                me->start_busy(2);
         } else
         {
                msg += CYN "可是$p" CYN "猛地向後一躍，跳出了$P"
                       CYN "的攻擊範圍。\n" NOR;
                me->start_busy(3);
         }
         message_combatd(msg, me, target);
         return 1;
}
