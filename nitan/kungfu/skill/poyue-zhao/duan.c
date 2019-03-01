#include <ansi.h>
#include <combat.h>

#define DUAN "「" HIY "斷脈破岳" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int i;

        if( userp(me) && !query("can_perform/poyue-zhao/duan", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(DUAN "只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail(DUAN "只能空手施展。\n");

        if ((int)me->query_skill("poyue-zhao", 1) < 80)
                return notify_fail("你破岳神爪不夠嫻熟，難以施展" DUAN "。\n");

        if (me->query_skill_mapped("claw") != "poyue-zhao")
                return notify_fail("你沒有激發破岳神爪，難以施展" DUAN "。\n");

        if (me->query_skill_prepared("claw") != "poyue-zhao")
                return notify_fail("你沒有準備破岳神爪，難以施展" DUAN "。\n");

        // 至于NPC麼…這個…還是用互背的好，互背時把CLAW提前就行了。
        if (userp(me) && me->query_skill_prepared("cuff") == "zhenyu-quan")
                return notify_fail("施展" DUAN "時破岳神爪不誼和鎮獄拳法互背。\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在真氣不足，難以施展" DUAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "霎時間只見$N" HIY "身形一展，雙爪疾攻而上，爪影籠罩$n"
              HIY "全身各處要穴。\n" NOR;
        message_combatd(msg, me, target);
        addn("neili", -50, me);

        for (i = 0; i < 4; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, 0, 0);
        }
        me->start_busy(1 + random(4));
        return 1;
}