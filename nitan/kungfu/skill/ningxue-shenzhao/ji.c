 // ji.c 疾電

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        mapping prepare;
        string msg;
        int skill;
        int delta;
        int i;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( userp(me) && !query("can_perform/ningxue-shenzhao/ji", me) )
                return notify_fail("你還不會使用這一招！\n");

        if (! me->is_fighting(target))
                return notify_fail("「疾電」只能對戰鬥中的對手使用。\n");

        if (me->query_skill_prepared("claw") != "ningxue-shenzhao")
                return notify_fail("你沒有準備使用凝血神爪，無法施展「疾電」。\n");

        skill = me->query_skill("ningxue-shenzhao", 1);

        if (skill < 250)
                return notify_fail("你的凝血神爪修為有限，無法使用「疾電」！\n");

        if (me->query_skill("force") < 350)
                return notify_fail("你的內功火候不夠，難以施展「疾電」！\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你的內力修為沒有達到那個境界，無法運轉內力形成「疾電」！\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠，現在無法施展「疾電」！\n");

        if( query_temp("weapon", me) )
                return notify_fail("你必須是空手才能施展「疾電」！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIR "$N" HIR "仰天一聲長嘯，飛身躍起，雙爪幻出漫天爪影，氣勢恢弘，宛如疾電一般籠罩$n" HIR "各處要穴！\n" NOR;

        message_combatd(msg, me, target);

        addn("neili", -300, me);
        addn_temp("apply/parry", delta, target);
        addn_temp("apply/dodge", delta, target);
        for (i = 0; i < 7; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, 0);
        }
        addn_temp("apply/parry", -delta, target);
        addn_temp("apply/dodge", -delta, target);
        me->start_busy(1 + random(5));

        return 1;
}
