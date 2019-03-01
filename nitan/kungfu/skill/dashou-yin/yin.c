// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIY "金剛印" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        skill = me->query_skill("dashou-yin", 1);

        if (skill < 100)
                return notify_fail("你的大手印修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<150 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("hand") != "dashou-yin")
                return notify_fail("你沒有激發大手印，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("hand") != "dashou-yin")
                return notify_fail("你沒有準備大手印，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "面容莊重，單手攜著勁風朝$n" HIY "猛然拍出，正"
              "是密宗絕學「金剛印」。\n" NOR;

        ap = attack_power(me, "hand");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -100, me);
                me->start_busy(2);
                damage = damage_power(me, "hand");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                           HIR "結果$p" HIR "招架不及，被$P" HIR
                                           "這一下打得七竅生煙，吐血連連。\n" NOR);
        } else
        {
                addn("neili", -40, me);
                msg += CYN "可是$p" CYN "不慌不忙，巧妙的架開了$P"
                       CYN "的金剛印。\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

