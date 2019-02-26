#include <ansi.h>
#include <combat.h>

#define HUAN "「" HIG "陰陽環" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, attack_time;

        if( userp(me) && !query("can_perform/yinyang-ren/huan", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUAN "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || (query("skill_type", weapon) != "sword"
            && query("skill_type", weapon) != "blade") )
                return notify_fail("你使用的武器不對，難以施展" HUAN "。\n");

        if (me->query_skill("yinyang-ren", 1) < 180)
                return notify_fail("你的陰陽刃法修為不夠，難以施展" HUAN "。\n");

        if (me->query_skill("dodge") < 220)
                return notify_fail("你的陰陽刃法修為不夠，難以施展" HUAN "。\n");

        if( query("neili", me)<270 )
                return notify_fail("你的真氣不夠，難以施展" HUAN "。\n");

        if (me->query_skill_mapped("sword") != "yinyang-ren"
            && me->query_skill_mapped("blade") != "yinyang-ren")
                return notify_fail("你沒有激發陰陽刃法，難以施展" HUAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "$N" HIY "長嘯一聲，手中" + weapon->name() + HIY "化出"
              "無數光環，猛然間光芒瀑漲，連連灑向$n" HIY "。\n" NOR;

        // 根據所激發的是sword或blade來判斷ap值。
        if (me->query_skill_mapped("sword") == "yinyang-ren")
                ap = me->query_skill("sword");
        else 
                ap = me->query_skill("blade");

        dp = target->query_skill("dodge");
        attack_time = 4;

        if (ap / 2 + random(ap * 2) > dp)
        {
                msg += HIR "結果$n" HIR "被$N" HIR "攻了個措手不及，$n"
                       HIR "慌忙招架，心中叫苦。\n" NOR;
                count = ap / 12;
                attack_time += random(ap / 45);
                addn_temp("apply/attack", count, me);
        } else
        {
                msg += HIC "$n" HIC "見$N" HIC "這幾招凌厲無比，兇猛異"
                       "常，只得苦苦招架。\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        if (attack_time > 8)
                attack_time = 8;

        addn("neili", -attack_time*20, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(attack_time));

        return 1;
}