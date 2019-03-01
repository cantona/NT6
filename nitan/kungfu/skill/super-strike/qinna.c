// by darken@SJ

inherit F_SSERVER;
#include <ansi.h>

string perform_name(){ return HBBLU"鐵掌擒拿"NOR; }
int perform(object me, object target)
{
        string msg;
        if( !target ) target = offensive_target(me);
        if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) )
                return notify_fail("「鐵掌擒拿手」只能對戰鬥中的對手使用。\n");
        if( (int)me->query_skill("force", 1) < 150 )
                return notify_fail("你的歸元吐納法修為未到，無法使出鐵掌擒拿手。\n");
        if( (int)me->query_skill("dodge", 1) < 150 )
                return notify_fail("你的水上漂修為未到，無法使出鐵掌擒拿手。\n");
        if( (int)me->query_skill("super-strike", 1) < 150 )
                return notify_fail("你的鐵掌修為未到，無法使出鐵掌擒拿手。\n");
        if( (int)me->query("jingli") < 1000 )
                return notify_fail("你現在精力太弱，不能出鐵掌擒拿手。\n");
        if (target->is_busy())
                return notify_fail("他已經被擊中了，不需要再使用鐵掌擒拿手。\n");

        me->start_perform(4,"鐵掌擒拿手");

        msg = HBBLU"\n$N使出鐵掌擒拿手，看準$n的手腕，一把抓去！\n"NOR;
        if (random(me->query_dex()) > target->query_dex() || random(me->query_str()) > target->query_str())
        {
                msg = HIR"\n$N鐵掌擒拿手一把抓住$n手腕，往外一扳，$n劇痛下只得停止攻擊，採取守勢。\n"NOR;
                target->set_temp("lost_attack",3+random(3));
                if (!target->is_busy()) target->start_busy(3);
        }
        else {
                me->start_busy(1);
                target->start_busy(1);
                msg += HIR"$n向$N急攻數招，$N只得回手自救。\n"NOR;
        }
        me->add("jingli",-(200+random(100)));
        message_vision(msg, me, target);
        return 1;
}
