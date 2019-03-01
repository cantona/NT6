// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIM "達摩亂氣劍" NOR; }

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不對，難以施展" + name() + "。\n");

        if ((int)me->query_skill("damo-jian", 1) < 250)
                return notify_fail("你達摩劍法不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "damo-jian")
                return notify_fail("你沒有激發達摩劍法，難以施展" + name() + "。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的內力修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIM "$N" HIM "回轉劍鋒，手中" + weapon->name() +
              HIM "紫光盪漾，如作龍吟，無形劍氣籠罩$n"
              HIM "全身。\n" NOR;

        ap = attack_power(me, "sword") + me->query_skill("force");
        dp = defense_power(target, "force") + target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                damage+= query("jiali", me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 95,
                                           (: final, me, target, damage :));
                me->start_busy(2);
                addn("neili", -200, me);
        } else
        {
                msg += CYN "可是$n" CYN "內力深厚，使得$P"
                       CYN "這一招沒有起到任何作用。\n" NOR;
                me->start_busy(3);
                addn("neili", -100, me);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        int lvl = me->query_skill("damo-jian", 1);

        target->affect_by("damo_luanqi",
                ([ "level"    : lvl + random(lvl),
                   "id":query("id", me),
                   "duration" : lvl / 50 + random(lvl / 20) ]));

        return  HIR "霎時$n" HIR "心頭一陣迷惑，體內的真氣登時"
                "不聽使喚，四處遊走。\n" NOR;
}
