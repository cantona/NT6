// pozhang.c 「破掌式」
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, weapon2, target;
        int skill, ap, dp, wound;

        if( query("family/master_id", me) != "fengqingyang" )
           return notify_fail("你不是風清揚的弟子，不能使用絕招！\n");

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("lonely-sword",1);

        if( !(me->is_fighting() ))
            return notify_fail("「破掌式」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
            return notify_fail("你使用的武器不對。\n");

        if( objectp(weapon2=query_temp("weapon", target)) )
            return notify_fail("對方手裏拿了武器，你用不了「破掌式」。\n");

        if( skill < 70)
            return notify_fail("你的獨孤九劍等級不夠, 不能使用「破掌式」！\n");

        if( query("neili", me)<50 )
            return notify_fail("你的內力不夠，無法運用「破掌式」！\n");

        msg = HIC "$N使出獨孤九劍之「破掌式」, 勁力聚在劍尖，企圖以意使劍.\n";
        message_combatd(msg, me, target);

        ap=query("combat_exp", me)+skill*1000;
        dp=query("combat_exp", target)/4;
        if( dp < 1 )
            dp = 1;
        if( random(ap) > dp )
        {
            if(userp(me))
                 addn("neili", -50, me);
            msg = "$N運起「破掌式」, $n頓時覺得眼前一花，手心一涼，手掌中心一
截劍尖冒了出來。\n"NOR;

//            wound = 60 + random(skill);
            wound = (int)me->query_skill("sword",1)/2 + skill;
            wound = wound/2 + random(wound);
// modify by Java
            if( wound>query("qi", target) )
                wound=query("qi", target);
            me->start_busy(random(2));
//            target->addn("qi", -wound);
//            target->addn("eff_qi", -wound);
            target->receive_damage("qi", wound);
            target->receive_wound("qi", wound/2);
// modify by Java
            target->start_busy(2);
        }
        else
        {
            if(userp(me))
                addn("neili", -100, me);
            msg = "可是$n看破了$N的企圖，全力防守，堪堪抵住了$N的攻勢。\n"NOR;
            me->start_busy(random(3));
        }
        message_combatd(msg, me, target);
        return 1;
}
int help(object me)
{
        write(WHT"\n獨孤九劍之破掌式："NOR"\n");
        write(@HELP

        使用功效：
                破解空手搏擊的敵手之招數，並傷敵氣血

        出手要求：
                身為風清揚嫡傳弟子
                獨孤九劍50級
                內力50
HELP
        );
        return 1;
}
