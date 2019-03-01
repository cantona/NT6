// pobian.c 破鞭式
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
            return notify_fail("「破鞭式」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
            return notify_fail("你使用的武器不對。\n");

        if( !objectp(weapon2=query_temp("weapon", target) )
         || query("skill_type", weapon2) != "hammer"
         || query("skill_type", weapon2) != "dagger"
         || query("skill_type", weapon2) != "axe" )
            return notify_fail("對方不使鞭、錘或斧頭，你用不了「破鞭式」。\n");

        if( skill < 50)
            return notify_fail("你的獨孤九劍等級不夠, 不能使用「破鞭式」！\n");

        if( query("neili", me)<50 )
            return notify_fail("你的內力不夠，無法運用「破鞭式」！\n");

        msg = HIC "$N巧使獨孤九劍「破鞭式」逼近$n，提劍幻出重重劍影，如
柔絲般向$n裹去。\n";
        message_combatd(msg, me, target);

        damage = 10 + random(skill / 2);
        ap = me->query_skill("sword") + skill;
        dp = target->query_skill("hammer") / 2;
        if( dp < 1 )
        if( dp < 1 )
            dp = 1;
        if( random(ap) > dp)
        {
            if(userp(me))
                 addn("neili", -50, me);
            msg = "$n頓時覺得壓力驟增，手腕一麻，手中";
            msg += weapon2->name();
            msg += "脫手而出！\n" NOR;

            me->start_busy(random(2));
            target->receive_damage("qi", damage);
            target->start_busy(2);
            weapon2->move(environment(me));
/*
            if( query("ownmake", weapon2) == 1 )
            {
                weapon2->move(target);
                msg += "那可是$n的隨身家伙！$n手一伸將它撿回來。\n" NOR;
            }
*/
        }
        else
        {
            if(userp(me))
                 addn("neili", -30, me);
            msg = "可是$n看破了$N的劍路，立刻採取守勢，使$N的破鞭式沒有起到
什麼作用。\n"NOR;
            me->start_busy(4);
        }
        message_combatd(msg, me, target);

        return 1;
}
int help(object me)
{
        write(WHT"\n獨孤九劍之破鞭式："NOR"\n");
        write(@HELP

        使用功效：
                破解且可擊落手持鞭類兵器的敵手之兵器，並傷敵氣血

        出手要求：
                身為風清揚嫡傳弟子
                獨孤九劍50級
                內力50
HELP
        );
        return 1;
}
