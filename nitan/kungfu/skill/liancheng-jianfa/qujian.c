// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "去劍勢"; }

int perform(object me, object target)
{
        object weapon;
        object obj;
        string msg;
        int ap, dp;

        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character() )
                return notify_fail("去劍勢只能對對手使用。\n");

        if( me->query_skill("liancheng-jianfa") < 80 )
                return notify_fail("你的連城劍法不夠嫻熟，不能施用去劍勢。\n");

        if( !objectp(weapon=query_temp("weapon", target)) )
                return notify_fail("對手並沒有使用武器。\n");

        msg = "$N清嘯一聲，抖直手中的兵刃，以連城劍法的去劍勢順勢搭上了$n的兵器！\n";

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(1);
                msg += HIY "只聽得一陣金鐵交鳴之聲，結果$p的兵刃被$P手中的兵器一連一帶，遠遠地飛了開去！\n" NOR;
                obj=query_temp("weapon", target);
                obj->unequip();
                obj->move(environment(me));

                target->start_busy(1 + random(4));
        } else
        {
                msg += "可是$p看破了$P的企圖，並沒有上當。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);
        return 1;
}