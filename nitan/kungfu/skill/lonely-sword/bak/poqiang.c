// poqiang.c 「破槍式」
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, weapon2, target;
        int skill, ap, dp, damage;

        if( query("family/master_id", me) != "fengqingyang" )
           return notify_fail("你不是風清揚的弟子，不能使用絕招！\n");

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("lonely-sword",1);

        if( !(me->is_fighting() ))
            return notify_fail("「破槍式」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
            return notify_fail("你使用的武器不對。\n");

        if( !objectp(weapon2=query_temp("weapon", target)) || 
            (query("skill_type", weapon2) != "spear" && 
             query("skill_type", weapon2) != "club" && 
             query("skill_type", weapon2) != "staff") )
            return notify_fail("對方沒有使槍棒，你用不了「破槍式」。\n");

        if( skill < 50)
            return notify_fail("你的獨孤九劍等級不夠, 不能使用「破槍式」！\n");

        if( query("neili", me)<50 )
            return notify_fail("你的內力不夠，無法運用「破槍式」！\n");

        msg = HIC "$N一式獨孤九劍「破槍式」，劍勢靈巧地順著"+weapon2->name()
+"削落，劃向$n的五指。\n";
        message_combatd(msg, me, target);
        damage = 10 + random(skill / 2);
        ap = me->query_skill("sword") + skill;
        if( query("skill_type", weapon2) == "staff" )
            dp = target->query_skill("staff") / 2;
        else if( query("skill_type", weapon2) != "club" )
            dp = target->query_skill("club") / 2;

        if( dp < 1 )
            dp = 1;
        if( random(ap) > dp )
        {
            if(userp(me))
                 addn("neili", -50, me);
            msg = "$N運起「破槍式」, $n頓時大驚，為保手指，手中";
            msg += weapon2->name();
            msg += "撒手丟出！\n" NOR;

            me->start_busy(random(2));
            target->receive_damage("qi", damage);
            target->start_busy(2);
            weapon2->move(environment(me));
        }
        else
        {
            if(userp(me))
                 addn("neili", -30, me);
            msg = "可是$n看破了$N的劍路，舍命將手中" + weapon2->name()+
"向前急刺，迫使$N收回攻勢！\n"NOR;
            me->start_busy(4);
        }
        message_combatd(msg, me, target);

        return 1;
}
int help(object me)
{
        write(WHT"\n獨孤九劍之破槍式："NOR"\n");
        write(@HELP

        使用功效：
                破解且可擊落手持槍類兵器的敵手之兵器，並傷敵氣血

        出手要求：
                身為風清揚嫡傳弟子
                獨孤九劍50級
                內力50
HELP
        );
        return 1;
}
