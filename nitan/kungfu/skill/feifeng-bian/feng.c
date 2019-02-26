// This program is a part of NT MudLIB
// feng.c 鳳朝凰

#include <ansi.h>

#include <combat.h>
inherit F_SSERVER;

string name() { return "鳳朝凰"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
        int count;
        int i;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail( "鳳朝凰只能在戰鬥中使用\n");


        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對。\n");


        if (me->query_skill("force") < 150)
                return notify_fail("你的內功的修為不夠，不能使用「鳳朝凰」！\n");

        if (me->query_skill("feifeng-bian", 1) < 150)
                return notify_fail("你的飛鳳鞭法修為不夠，目前不能使用「鳳朝凰」！\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠，無法使用「鳳朝凰」！\n");

        if (me->query_skill_mapped("whip") != "feifeng-bian")
                return notify_fail("你沒激發飛鳳鞭法，不能使用「鳳朝凰」！\n");

        msg = HIY "$N" HIY "衝着" HIY "$n" HIY "輕佻一笑，向前急衝,手中" + weapon->name() +
              HIY "卻毫不停留，一招「鳳朝凰」\n"
              HIY "如凰洗空，長鳳戲羽，"
              HIY "亂雨傾盆般分點" HIY "$n" HIY "左右!! \n" NOR;

        ap = attack_power(me, "whip");
        if (living(target))
                 dp = defense_power(target, "parry");
        else     dp = 0;

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "結果$p" HIR "被$P" HIR
                       "攻了個措手不及，目接不暇，疲於奔命！\n" NOR;
                count = ap;

                addn_temp("apply/attack", count, me);

        } else
        {
                msg += HIC "$n" HIC "見$N" HIC "鞭勢狠辣，心下凜然，凝神應付。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);

        addn("neili", -150, me);
        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(4));
        return 1;
}