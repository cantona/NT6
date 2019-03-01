// riyue.c 斷雲鞭法[日月無光]

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        string msg;

        if( !target ) target = offensive_target(me);

        if( !target
        ||        !target->is_character()
        ||        !me->is_fighting(target) )
                return notify_fail("牽制攻擊只能對戰鬥中的對手使用。\n");

        if( (int)me->query_skill("shigu-bifa",1) < 100)
                return notify_fail("你的「石鼓打穴筆法」還沒學到家，用不了「點穴」絕招。\n");

        if( (int)me->query_skill("wuzheng-xinfa",1) < 100)
                return notify_fail("你的「無爭心法」不夠純熟，用不了「點穴」絕招。\n");

        if( target->is_busy() )
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        msg = HIC "$N大筆虛點，自右上角至左下角彎曲而下，勁力充沛，$n上半身穴道皆籠罩其中。\n"NOR;

        if( random(query("combat_exp", me)/100)>query("combat_exp", target)/300){
                msg += HIW"$p感到雙手、胸口、腹部、三處穴道微微一痛，頓時全身麻木不能動彈。\n" NOR;
                target->start_busy( (int)me->query_skill("shigu-bifa") / 30 +4);
                me->start_busy(random(2));
                addn("neili", -200, me);
        } else {
                msg += HIR"可是$p看破了$P的企圖，並沒有上當。\n" NOR;
                me->start_busy(2);
        }
        message_vision(msg, me, target);

        return 1;
}