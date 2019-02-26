#include <ansi.h>
#include <combat.h>

#define RIYUE "「" HIY "日月乾坤" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, attack_time;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( userp(me) && !query("can_perform/qiankun-jian/riyue", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(RIYUE "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" RIYUE "。\n");

        if (me->query_skill("force") < 220)
                return notify_fail("你的內功的修為不夠，難以施展" RIYUE "。\n");

        if (me->query_skill("qiankun-jian", 1) < 150)
                return notify_fail("你的乾坤神劍修為不夠，難以施展" RIYUE "。\n");

        if( query("neili", me)<400 )
                return notify_fail("你的真氣不夠，難以施展" RIYUE "。\n");

        if (me->query_skill_mapped("sword") != "qiankun-jian")
                return notify_fail("你沒有激發乾坤神劍，難以施展" RIYUE "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "只見$N" HIY "手中" + weapon->name() + HIY
              "一顫，將乾坤劍法連環施出，頓時幻出無數劍影，"
              "鋪天蓋地向$n" HIY "席捲而去！\n" NOR;

        ap = me->query_skill("sword");
        dp = target->query_skill("parry");
        attack_time = 4;

        if (ap / 2 + random(ap * 2) > dp)
        {
                msg += HIR "$n" HIR "只覺劍影重重，登時眼花繚"
                       "亂，被攻了個措手不及，疲於奔命。\n" NOR;
                count = ap / 10;
                addn_temp("apply/attack", count, me);
                attack_time += random(ap / 45);
        } else
        {
                msg += HIC "$n" HIC "見$N" HIC "劍招洶湧，氣"
                       "勢恢弘，急忙凝神聚氣，小心應付。\n"
                       NOR;
                count = 0;
        }
                
        message_combatd(msg, me, target);

        if (attack_time > 6)
                attack_time = 6;

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
