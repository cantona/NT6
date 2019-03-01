// This program is a part of NITAN MudLIB
// huang.c 地老天荒

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "地老天荒"; }

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
                return notify_fail("「地老天荒」只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) )
                return notify_fail("必須空手才能施展「地老天荒」。\n");

        if (me->query_skill_mapped("strike") != "tianchang-zhang")
                return notify_fail("你沒有激發天長掌法，無法施展「地老天荒」。\n");

        skill = me->query_skill("tianchang-zhang", 1);

        if (skill < 100)
                return notify_fail("你的天長掌法修為有限，不能使用「地老天荒」！\n");

        if( query("neili", me)<150 )
                return notify_fail("你的真氣不夠，無法運用「地老天荒」！\n");

        if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIR "$N" HIR "“□”的一聲震喝，提起掌來，只見掌心一片血紅，倏的凌空拍出，"
              HIR "一股熱風登時襲向$n" HIR "的胸前大穴。\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -120, me);
                me->start_busy(2);
                damage = damage_power(me, "strike");
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 50,
                                           HIR "$n" HIR "一時間只覺得氣血上湧，渾"
                                           "身如遭火焚，氣息大亂，不由得吐了一口"
                                           "鮮血。\n" NOR);
        } else
        {
                addn("neili", -50, me);
                msg += HIC "然而$n" HIC "內功深湛，絲毫不為$N"
                       HIC "的掌風所動，若無其事" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}