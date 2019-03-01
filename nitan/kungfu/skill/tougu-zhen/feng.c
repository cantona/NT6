#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "封殺" NOR; }

string final(object me, object targer, int lvl);

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage;
        int lvl;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中使用。\n");

        if ((int)me->query_skill("tougu-zhen", 1) < 100)
                return notify_fail("你的透骨針還不夠嫻熟，無法施展" + name() + "！\n");

        if ((int)me->query_skill("force") < 260)
                return notify_fail("你內功火候不夠，難以施展" + name() + "！\n");

        if ((int)query("max_neili", me) < 2400)
                return notify_fail("你的真氣不夠，無法施展" + name() + "！\n");

        if ((int)query("neili", me) < 350)
                return notify_fail("你的真氣不夠，無法施展" + name() + "！\n");

        if (me->query_skill_prepared("finger") != "tougu-zhen")
                return notify_fail("你沒有準備使用透骨針，無法使用" + name() + "！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N" HIW "使出透骨針「" HIR "封 殺" HIW "」絕技，手指揮舞，幻出漫天寒星"
              "，攜帶著陰寒之勁直封$n" HIW "各處要穴！\n" NOR;

        lvl = me->query_skill("tougu-zhen", 1);

        ap = attack_power(me, "finger") + me->query_skill("force");
        dp = defense_power(target, "parry") + target->query_skill("dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "finger");

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 65,
                                           (: final, me, target, lvl :));

                addn("neili", -280, me);
                me->start_busy(1);
        } else
        {
                msg += CYN "可是$n急忙退閃，連消帶打躲開了這一擊。\n" NOR;
                me->start_busy(3);
                addn("neili", -50, me);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int lvl)
{
       target->affect_by("tougu_zhen",
                        ([ "level"    : query("jiali", me) + random(query("jiali", me)),
                           "id"       : query("id", me),
                           "duration" : lvl / 50 + random(lvl / 20) ]));

        return HIR "結果只聽$n一聲慘嚎，被攻個正著，透骨針極寒之勁攻心，全身癱麻，鮮血狂噴！\n" NOR;
}