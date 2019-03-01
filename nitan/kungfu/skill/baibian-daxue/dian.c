// This program is a part of NITAN MudLIB
// dian.c 點字訣

#include <ansi.h>

inherit F_SSERVER;

string name() { return "點字訣"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「點字訣」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "staff" )
                return notify_fail("運用「點字訣」手中必須持杖！\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠！\n");

        if ((int)me->query_skill("staff") < 150)
                return notify_fail("你的杖法還不到家，無法使用「點字訣」！\n");

        if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIG "$N" HIG "手中的" + weapon->name() +
              HIG "忽然變得詭秘異常，忽伸忽縮，籠罩了$n" HIG "多處大穴！\n" NOR;

        ap = attack_power(me, "staff");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIY "$n" HIY "大驚之下，慌忙抵擋，一時間無暇反擊！\n" NOR;
                target->start_busy(ap / 90 + 2);
        } else
        {
                msg += HIC "可是$p" HIC "身法靈動，躲開了$n" HIC "的纏身進擊！" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}