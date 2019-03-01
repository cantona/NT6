// This program is a part of NITAN MudLIB
// six.c 六脈劍氣

#include <ansi.h>

inherit F_SSERVER;

string name() { return HIW "六脈劍氣" NOR; }

int perform(object me, object target)
{
        mapping prepare;
        string msg;
        int skill;
        int delta;
        int i, ap, dp;
        int n;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if (me->query_skill_prepared("finger") != "six-finger")
                return notify_fail("你沒有準備使用六脈神劍，無法施展" + name() + "。\n");

        skill = me->query_skill("six-finger", 1);

        if (skill < 220)
                return notify_fail("你的六脈神劍修為有限，無法使用" + name() + "！\n");

        if (me->query_skill("force") < 400)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "！\n");

        if( query("max_neili", me)<7000 )
                return notify_fail("你的內力修為沒有達到那個境界，無法運轉內"
                                   "力形成" + name() + "！\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠，現在無法施展" + name() + "！\n");

        if( query_temp("weapon", me) )
                return notify_fail("你必須是空手才能施展" + name() + "！\n");

        if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "攤開雙手，手指連彈，霎時間空氣炙熱，幾"
              "欲沸騰，六道劍氣分自六穴，一起殺向$n" HIY "！\n" NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                delta = skill / 2;
                if( (n = me->query_skill("qimai-liuzhuan", 1) / 100) >= 1 )
                {
                        msg += HIM"$N"HIM"運用氣脈流轉的輔助，使得六脈劍氣傷害更強。\n"NOR;
                        delta += delta * n * 15 / 100;
                }
                msg += HIR "$n" HIR "見此劍氣縱橫，微一愣神，不禁心萌退意。\n" NOR;
        } else
                delta = 0;

        message_combatd(msg, me, target);

        addn("neili", -300, me);
        addn_temp("apply/attack", delta, me);
        addn_temp("apply/defense", delta, me);
        addn_temp("apply/unarmed_damage", delta, me);
        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);
                set_temp("six-finger/hit_msg", i, me);
                COMBAT_D->do_attack(me, target, 0, 0);
        }
        addn_temp("apply/attack", -delta, me);
        addn_temp("apply/defense", -delta, me);
        addn_temp("apply/unarmed_damage", -delta, me);
        delete_temp("six-finger/hit_msg", me);
        me->start_busy(1 + random(3));

        return 1;
}
