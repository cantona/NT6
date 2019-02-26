// snake.c  金蛇遊身

#include <ansi.h>
#include <combat.h>
// inherit F_CLEAN_UP;
inherit F_SSERVER;
void remove_effect(object me, int amount);

int perform(object me, object target)
{
       object ob;
        int skill,tg_skill,time;
        string msg;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("「金蛇遊身」只能對戰鬥中的對手使用。\n");

        if( (int)me->query_skill("wudu-yanluobu", 1) < 50 )
                return notify_fail("你的五毒煙蘿步火候不夠，不能使出「金蛇遊身」。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在內力太弱，不能使用「金蛇遊身」。\n");

        if( target->is_busy() )
                return notify_fail(target->name() + "目前正手忙腳亂，你還亂轉什麼，趕快進攻吧！\n");
                        
        msg = HIC "$N身行忽的一變，使出「金蛇遊身」的絕技，身法越來越快。\n\n\n只見$N飛快的繞場遊走，瞻之在前，望之在後，一時間到處都是$N的身影。\n"NOR;
        message_vision(msg, me, target);
       time = (int)me->query_skill("wudu-yanluobu",1)/25;
       skill = (int)me->query_skill("wudu-yanluobu",1)
             + (int)me->query_skill("dodge",1);
       tg_skill = (int)target->query_skill("dodge",1);
        addn("neili", -100, me);
       if (random(skill) > random(tg_skill))
       {
       target->start_busy(random(time)+3);
        msg = HIR"$n不由得一陣手足無措，被$N連攻數招！\n"NOR;
        message_vision(msg, me, target);
       return 1;
        }
       else
        {
       me->start_busy(4);
        msg = HIR"可是$n以靜制動，緊守門户，絲毫不受$N的影響,$N自己倒累的滿頭大汗！\n"NOR;
        message_vision(msg, me, target);
       }
        return 1;
}
