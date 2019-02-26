#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "佛光普照" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("你必須空手才能施展" + name() + "。\n");

        if (me->query_skill("force") < 300)
                return notify_fail("你的內功的修為不夠，無法施展" + name() + "。\n");

        if (me->query_skill("piaoxue-zhang", 1) < 180)
                return notify_fail("你的飄雪穿雲掌修為不夠，無法施展" + name() + "。\n");

        if( query("neili", me)<1000 || query("max_neili", me)<3500 )
                return notify_fail("你的真氣不夠，無法施展" + name() + "。\n");

        /*
        if (me->query_skill_mapped("force") != "emei-jiuyang" &&
            me->query_skill_mapped("force") != "wudang-jiuyang" &&
            me->query_skill_mapped("force") != "shaolin-jiuyang" &&
            me->query_skill_mapped("force") != "jiuyang-shengong")
                return notify_fail("你沒有激發內功為九陽神功，無法施展" + name() + "。\n");
        */

        if (me->query_skill_mapped("strike") != "piaoxue-zhang")
                return notify_fail("你沒有激發飄雪穿雲掌，無法施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "piaoxue-zhang")
                return notify_fail("你沒有準備飄雪穿雲掌，無法施展" + name() + "。\n");

        if( !query_temp("powerup", me) )
                return notify_fail("你必須將全身功力盡數提起才能施展" + name() + "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "$N" HIY "運起全身功力，頓時真氣迸發，全身骨骼噼啪作"
              "響，猛然一掌向$n" HIY "\n全力拍出，力求一擊斃敵，正是一"
              "招「佛光普照」。\n" NOR;

        ap = attack_power(me, "strike") +
             me->query_skill("force") +
             query("str", me)*10;

        dp = defense_power(target, "dodge") +
             target->query_skill("force") +
             query("con", me)*10;

        if (target->query_skill_mapped("force") == "jiuyang-shengong")
        {
                addn("neili", -800, me);
                me->start_busy(5);
                msg += HIW "只聽轟然一聲巨響，$n" HIW "已被一招正中，可$N"
                       HIW "只覺全身內力猶如江河入\n海，又如水乳交融，登"
                       "時消失得無影無蹤。\n" NOR;
        } else
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike") + me->query_skill("mahayana", 1);
                addn("neili", -800, me);
                me->start_busy(3);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
                                           HIR "只聽轟然一聲巨響，$n" HIR "被$N"
                                           HIR "一招正中，身子便如稻草般平平飛出"
                                           "，重\n重摔在地下，嘔出一大口鮮血，動"
                                           "也不動。\n" NOR);
        } else
        {
                addn("neili", -500, me);
                me->start_busy(4);
                msg += CYN "可是$p" CYN "內力深厚，及時擺脱了"
                       CYN "$P" CYN "內力的牽扯，躲開了這一擊！\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
