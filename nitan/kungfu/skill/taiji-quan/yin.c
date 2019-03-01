// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "引字訣" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, ap, dp, damage;
        string msg;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        skill = me->query_skill("taiji-quan", 1);

        if (skill < 150)
                return notify_fail("你的太極拳等級不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("cuff") != "taiji-quan")
                return notify_fail("你沒有激發太極拳，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("cuff") != "taiji-quan")
                return notify_fail("你現在沒有準備使用太極拳，無法使用" + name() + "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N" HIW "雙手一圈，施出「引」字訣，如抱太極，一股"
              "雄渾無比的力道組成了一個旋渦，圈向$n" HIW "。\n" NOR;
        addn("neili", -100, me);

        ap = attack_power(me,"cuff");
        dp = defense_power(target,"parry");

        if (ap / 2 + random(ap * 4 / 3) > dp)
        {
                addn("neili", -10, me);
                damage = damage_power(me, "cuff");
                damage+= query("jiali", me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                           HIR "$n" HIR "微微一楞，登時被這力道帶"
                                           "得在原地急轉七八下，如轉陀螺，如旋紡"
                                           "錘。\n" NOR);
                me->start_busy(2);
                if (ap / 2 + random(ap) > dp && ! target->is_busy())
                        target->start_busy(ap / 60 + 3);
        } else
        {
                msg += CYN "$n" CYN "見狀連忙使出“千斤墜”之力定"
                       "住身形，擺脫了$N" CYN "的力道。\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
