// 劍動莫名

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "劍動莫名"; }
int perform(object me, object target)
{
        object weapon, ob;
        string msg;
        int i,j,times,n;

        i = me->query_skill("wuming-jianfa", 1)/60;
        j = me->query_skill("sword")/60;

        if (! target) 
        {
                me->clean_up_enemy(); 
                target = me->select_opponent(); 
        }
        if (! target || ! me->is_fighting(target)) 
                return notify_fail("你只能對戰鬥中的對手使用絕招「劍動莫名」。\n"); 
        if( !objectp(weapon=query_temp("weapon", me)))return notify_fail("你必須使用武器才能使用「劍動莫名」！\n");
        //if ( base_name(weapon)!="/clone/weapon/yuenv" ) return notify_fail("你必須手持越女朝陽劍才能使用「劍動莫名」！\n");
        if ( (int)me->query_str() < 35 ) return notify_fail("你的臂力不夠, 還不能使用這項絕技! \n");
        if ( (int)me->query_skill("sword",1) < 600 ) return notify_fail("你的基本劍法的火候還不到家, 不能使用這一絕技 !\n");
        if ( (int)me->query_skill("wuming-jianfa", 1) < 500 ) return notify_fail("你的無名劍法的火候還不到家, 不能使用這一絕技 !\n");
        if( query("neili", me)<50000)return notify_fail("你的真氣不夠！\n");
        if( query("max_neili", me)<50000)return notify_fail("你的內力修為不夠！\n");
        if ( me->is_busy() ) return notify_fail("你上一個動作還沒有完成！\n");

        msg = MAG "\n$N臉現幽思,往事如潮湧上心頭,手中劍望空斜指一股怨氣從劍尖散發彌漫開來！\n" NOR;
        message_combatd(msg, me);
        ob = target;
        addn_temp("apply/str", i, me);
        addn_temp("apply/attack", j, me);
        times = (int)(me->query_skill("wuming-jianfa", 1)/50) - 1;
        if( times > 12 ) times = 12;
        for ( n=0; n<times; n++ )
        {
                if ( !ob ) break;
                COMBAT_D->do_attack(me,ob,query_temp("weapon", me),1);
        }
        addn_temp("apply/str", -i, me);
        addn_temp("apply/attack", -j, me);
        addn("neili", -random(5000)-5000, me);
        me->start_busy(random(2)+2);
        if ( ob && !ob->is_busy() ) ob->start_busy(random(2)+1);
        return 1;
}
