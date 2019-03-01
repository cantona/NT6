// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIY "光華令" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage, skill, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        skill = me->query_skill("shenghuo-ling",1);

        if (! (me->is_fighting()))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if (! objectp(weapon = query_temp("weapon", me)) ||
            (string)query("skill_type", weapon) != "sword")
                return notify_fail("你使用的兵器不對，不能使用聖火令法之" + name() + "。\n");

        if (skill < 140)
                return notify_fail("你的聖火令法等級不夠, 不能使用聖火令法之" + name() + "。\n");

        if (query("max_neili", me) < 1500)
                return notify_fail("你的內力修為不足，不能使用聖火令法之" + name() + "。\n");

        if (query("neili", me) < 340)
                return notify_fail("你的內力不夠，不能使用聖火令法之" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "猛吸一口氣，使出聖火令法之「" HIW "光華令" HIY "」，手中"
              + weapon->name() + NOR + HIY "御駕如飛，幻出無數道金"
              "芒，將$n" HIY "籠罩起來！\n" NOR;

        ap = attack_power(me, "sword") + me->query_skill("force");
        dp = defense_power(target, "parry") + target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");

                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                       HIR "$n" HIR "只覺萬道金芒舖天蓋地席卷而來，"
                       "完全無法阻擋。頓時只感全身幾處刺痛，鮮血飛"
                       "濺而出！\n" NOR);

                me->start_busy(2);
        } else
        {
                msg += CYN "可是$n" CYN "看準$N" CYN "的破綻，猛地向"
                       "前一躍，跳出了$N" CYN "的攻擊范圍。\n"NOR;
                addn("neili", -150, me);
                me->start_busy(4);
        }
        message_combatd(msg, me, target);
        return 1;
}
