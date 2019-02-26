#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "無形幻影" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int i;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你的武器不對，難以施展" + name() + "。\n");

        if ((int)me->query_skill("yanxing-dao", 1) < 60 )
                return notify_fail("你雁行刀法不夠嫻熟，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 120 )
                return notify_fail(RED"你內功火候不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "yanxing-dao")
                return notify_fail("你沒有激發雁行刀法，難以施展" + name() + "。\n");

        if( query("neili", me)<80 )
                return notify_fail(HIC"你現在真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIC "$N" HIC "大喝一聲，全場四處遊動，$n"
              HIC "只看到$N" HIC "化做數團身影，漫天刀"
              HIC "光席捲而來！\n"NOR;
        message_combatd(msg, me, target);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn("neili", -80, me);
        me->start_busy(1 + random(3));
        return 1;
}