// liumang.c 流氓神拳
// By Alf, Last Update 2001.11

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        int damage;
        string msg;

        if(!target) target = offensive_target(me);

        if(!target || !target->is_character() || !me->is_fighting(target))
                return notify_fail("你只能在戰鬥中使用這一絕招。\n");

    if((int)me->query_skill("liumang-shenquan", 1) < 80)
                return notify_fail("你的流氓神拳還不夠純熟，無法使出這一絕招。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的內力修為還不夠高。\n");

        msg = HIG"$N深深吸了口氣，氣運丹田，陡然間張嘴一聲狂喝：\n"NOR;
        msg += HIC"
I@@L      @@@@       I@@@ ezz,_zzzzzz_     @@@L     I@@I       zzzL  @@@' Izzz  
`@@@_I--zz@@~~-----  I@@@ I@@I     I@@I    `~~~ ezz_a@@bzz_,   `~~~,I@@@ I~~~'  
 `~~~ _@@@' `-@@L   zzzzzzI@@I     I@@I  '~~@@@ I@@'I@@II@@I  ~~~~~=@@@~~~~~~~~'
I@@L I@@@_____@@@L   @@@  I@@M~~@@@@~~     I@@P I@@ I@@II@@I ~~~~@@@@~~~-@@@~~~~
`-@@_ =@@~=== _=@~'  @@@  I@@I  I@@I      I@@@@bI@@~@@@@-@@I  ._a@@@=__d@@@@@L, 
  ==='I@@ I@@ @@@    @@@  I@@I--I@@I---  I@@@@M@a@@ I@@II@@I '~~~'   I@@I  ~~~~'
 d@@' I@@ I@@ @@@    @@@  I@@I  I@@L       I@@I I@@_I@@II@@P  `~~~~~~I@@I~~~~~' 
I@@@  I@@ I@@ @@@ .  @@@  I@@I  I@@I  _    I@@I '~~'I@@I~~'  ~~~~~~~~@@@@~~~~~~~
I@@I  a@@ I@@ @@@_%  ~-@bz`@@@zz-I@@zd~    I@@I     I@@I        I-z_z@@@P       \n"NOR;

        msg += HIY"\n跟着拳隨聲至，勢如急風驟雨一般，逕直擊往$n的胸腹要害！！！\n"NOR;  

        if( random(query("combat_exp", me))>query("combat_exp", target)/2 )
        { 
                me->start_busy(2+random(2));
                target->start_busy(4);

                damage = (int)me->query_skill("liumang-shenquan", 1)/3+(int)me->query_skill("unarmed",1)/3;
                damage = damage + random(damage);

                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage/2);
                addn("neili", -200, me);
                msg += HIR"$n耳際如遭雷殛，懵然不知閃避，被$N這招重重擊實，不由得長聲慘呼！\n"NOR;
        }

        else
        {
                msg += YEL"$n急忙作勢斜撲，一個就地十八滾，狼狽萬狀的躲開了$N這招。\n"NOR;
                me->start_busy(1);
        }

        message_vision(msg, me, target);

        if(!target->is_fighting(me)) target->fight_ob(me);
        if(userp(target)) target->fight_ob(me);
        else if( !target->is_killing(me) ) target->kill_ob(me);
        return 1;
}

