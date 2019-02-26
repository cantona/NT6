// poanqi.c 破箭式
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, weapon2, target;
        int skill, ap, dp, damage;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("lonely-sword",1);

        if( query("family/master_id", me) != "fengqingyang" )
           return notify_fail("你不是風清揚的弟子，不能使用絕招！\n");

        if( !(me->is_fighting() ))
            return notify_fail("「破箭式」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
            return notify_fail("你使用的武器不對。\n");

        if( !objectp(weapon2=query_temp("weapon", target) )
         || query("skill_type", weapon2) != "throwing" )
             return notify_fail("對方沒有使暗器，你用不了「破箭式」。\n");

        if( skill < 50)
            return notify_fail("你的獨孤九劍等級不夠, 不能使用「破箭式」！\n");

        if( query("neili", me)<50 )
            return notify_fail("你的內力不夠，無法運用「破箭式」！\n");

        msg = HIC "$N舉劍連點，運起獨孤九劍之「破箭式」, 將$n擲過來的"+ weapon2->name() + "打得向$n反擊回去。\n";
        message_combatd(msg, me, target);

        damage = 10 + random(skill / 2);
        ap = me->query_skill("sword") + skill;
        dp = target->query_skill("throwing", 1);
        if( dp < 1 )
                dp = 1;
          if( random(ap) > dp )
          {
             if(userp(me))
                  addn("neili", -50, me);
             msg = "$n頓時覺得鋪天蓋地的";
             msg += weapon2->name();
             msg += "反而向自己襲來！全身上下立刻被打得跟馬蜂窩似的\n" NOR;

             me->start_busy(random(2));
             target->receive_damage("qi", damage);
             target->start_busy(2);
        }
        else
        {
             if(userp(me))
                  addn("neili", -30, me);
             msg = "可是$n看破了$N的意圖，立刻將手中" + weapon2->name()+
"舞得風雨不透，將反擊回來的" + weapon2->name() + "盡數擊落在地。\n"NOR;
             me->start_busy(4);
        }
        message_combatd(msg, me, target);

        return 1;
}
int help(object me)
{
        write(WHT"\n獨孤九劍之破箭式："NOR"\n");
        write(@HELP

        使用功效：
                破解持暗器的對手，反激暗器傷敵氣血

        出手要求：
                身為風清揚嫡傳弟子
                獨孤九劍100級
                內力50
HELP
        );
        return 1;
}
