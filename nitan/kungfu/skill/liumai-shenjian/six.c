#include <ansi.h>

#define SIX "「" HIW "六脈劍氣" NOR "」"

inherit F_SSERVER;


int perform(object me, object target)
{
        mapping prepare;
        string msg;
        int skill;
        int delta;
        int i;

        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/liumai-shenjian/six", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(SIX "只能對戰鬥中的對手使用。\n");

        if (me->query_skill_prepared("finger") != "liumai-shenjian")
                return notify_fail("你沒有準備使用六脈神劍，無法施展" SIX "。\n");

        skill = me->query_skill("liumai-shenjian", 1);

        if (skill < 220)
                return notify_fail("你的六脈神劍修為有限，無法使用" SIX "！\n");

        if (me->query_skill("force") < 400)
                return notify_fail("你的內功火候不夠，難以施展" SIX "！\n");

        if( query("max_neili", me)<7000 )
                return notify_fail("你的內力修為沒有達到那個境界，無法運轉內"
                                   "力形成" SIX "！\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠，現在無法施展" SIX "！\n");

        if( query_temp("weapon", me) )
                return notify_fail("你必須是空手才能施展" SIX "！\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "$N" HIW "攤開雙手，手指連彈，霎時間空氣炙熱，幾"
              "欲沸騰，六道劍氣分自六穴，一起衝向$n" HIW "！\n" NOR;

        if( random(query("combat_exp", me)/200)>query("combat_exp", target)/300 )
        {
                msg += HIR "$n" HIR "只感劍氣縱橫，微一愣神，不禁心萌退意。\n" NOR;
                delta = skill / 6;
        } else
                delta = 0;

        message_combatd(msg, me, target);

        addn("neili", -400, me);
        addn_temp("apply/parry", delta, target);
        addn_temp("apply/dodge", delta, target);
        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);

                set_temp("liumai-shenjian/hit_msg", i, me);

                COMBAT_D->do_attack(me, target, 0, i * 3);
        }
        addn_temp("apply/parry", -delta, target);
        addn_temp("apply/dodge", -delta, target);
        delete_temp("liumai-shenjian/hit_msg", me);
        me->start_busy(1 + random(5));

        return 1;
}
