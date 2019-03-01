// This program is a part of NITAN MudLIB
// zhua.c 三陰毒爪

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "三陰毒爪" NOR; }

string final(object me, object target);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if ((int)me->query_skill("sanyin-zhua", 1) < 80)
                return notify_fail("你的三陰蜈蚣爪不夠嫻熟，無法使用" + name() + "。\n");

        if (me->query_skill_mapped("claw") != "sanyin-zhua")
                return notify_fail("你沒有激發三陰蜈蚣爪，無法使用" + name() + "。\n");

        if (me->query_skill_prepared("claw") != "sanyin-zhua")
                return notify_fail("你沒有準備使用三陰蜈蚣爪，無法使用" + name() + "。\n");

        if( query("neili", me)<350 )
                return notify_fail("你真氣不足，無法施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIR "$N" HIR "突然一聲怪叫，驀的面赤如血，隨即手腕一抖，抓向$n"
              HIR "的要害。\n" NOR;

        ap = attack_power(me, "claw");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "claw");
                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           (: final, me, target :));
                me->start_busy(2);
        } else
        {
                addn("neili", -50, me);
                msg += HIR "不過$p" HIR "看破了$P" HIR "的招式，"
                       "凝神招架，擋住了$P" HIR "的毒招。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target)
{
        int lvl;

        lvl = me->query_skill("claw");
        target->affect_by("sanyin",
                       (["level":query("jiali", me)*2+random(query("jiali", me)*3),
                          "id":query("id", me),
                          "duration" : lvl / 40 + random(lvl / 40) ]));

        return HIR "$p" HIR "驚慌失措，連忙後退，然而沒"
               "能避開，被$P" HIR "這一爪抓得鮮血淋漓！\n" NOR;
}
