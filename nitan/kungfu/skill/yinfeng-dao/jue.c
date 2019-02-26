#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "絕殺" NOR; }

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

        if ((int)me->query_skill("yinfeng-dao", 1) < 140)
                return notify_fail("你的陰風刀還不夠嫻熟，無法施展" + name() + "絕技！\n");

        if ((int)me->query_skill("force") < 260)
                return notify_fail("你內功火候不夠，難以施展" + name() + "絕技！\n");

        if ((int)query("max_neili", me) < 2400)
                return notify_fail("你的真氣不夠，無法施展" + name() + "絕技！！\n");

        if ((int)query("neili", me) < 400)
                return notify_fail("你的真氣不夠，無法施展" + name() + "絕技！！\n");

        if (me->query_skill_mapped("strike") != "yinfeng-dao")
                return notify_fail("你沒有激發陰風刀，無法使用" + name() + "絕技！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "$N" HIW "使出陰風刀「" HIR "絕 殺" HIW"」絕技，掌勁幻出一片片切骨寒"
              "氣如颶風般裹向$n全身！\n" NOR;

        lvl = me->query_skill("yinfeng-dao", 1);

        ap = attack_power(me, "strike") + me->query_skill("force");
        dp = defense_power(target, "parry") + me->query_skill("dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           (: final, me, target, lvl :));

                addn("neili", -350, me);
                me->start_busy(1);
        } else
        {
                msg += CYN "可是$n急忙退閃，連消帶打躲開了這一擊。\n" NOR;
                me->start_busy(3);
                addn("neili", -150, me);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int lvl)
{
       target->affect_by("yinfeng_dao",
                       ([ "level"    : query("jiali", me) + random(query("jiali", me)),
                          "id"       : query("id", me),
                          "duration" : lvl / 50 + random(lvl / 20) ]));

       return HIR "結果只聽$n一聲慘嚎，全身幾處要穴同時被陰風寒勁砍中，疼若刮骨，鮮血狂泄而出！\n" NOR;
}
