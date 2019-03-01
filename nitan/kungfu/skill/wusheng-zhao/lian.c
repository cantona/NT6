#include <ansi.h>
#include <combat.h>

string name() { return HIY "奪命連環" NOR; }

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能使用" + name() + "。\n");

        skill = me->query_skill("wusheng-zhao", 1);

        if (skill < 120)
                return notify_fail("你的五聖毒爪等級不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("claw") != "wusheng-zhao")
                return notify_fail("你沒有激發五聖毒爪，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("claw") != "wusheng-zhao")
                return notify_fail("你沒有準備使用五聖毒爪，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "身形一展，撲至$n" HIY "跟前，猛然施展「奪"
              "命連環」，雙爪幻作數道金光，直瑣$n" HIY "各處要脈！\n" NOR;

        ap = attack_power(me, "claw");
        dp = defense_power(target, "parry");
        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -150, me);
                damage = damage_power(me, "claw");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30,
                                           HIR "$p" HIR "奮力抵抗，結果還是連中$P"
                                           HIR "數抓，登時鮮血飛濺，無法反擊！\n" NOR);
                me->start_busy(1);
                if (ap / 3 + random(ap) > dp && ! target->is_busy())
                        target->start_busy(ap / 100 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "的看破了$P" CYN
                       "的招式，巧妙的一一拆解，沒露半點破綻！\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}