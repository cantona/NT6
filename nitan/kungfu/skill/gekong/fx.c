// fuxue.c 拈花指 「拈花拂穴」
#include <ansi.h>
inherit F_SSERVER;
int perform(object me, object target)
{
    int busy_time;
    if( (time()-query_temp("perform_time", me))<5 )
        return notify_fail("你積蓄真氣，準備再次使用拈花拂穴。\n");
    if( !target ) target = offensive_target(me);
    if( !target ) return notify_fail("你想點誰的穴位？\n");
    if( !target->is_character() || target->is_corpse() )
        return notify_fail("看清楚一點，那並不是活物。\n");
    if((int)me->query_str() < 25)
        return notify_fail("你臂力不夠,不能使用這一絕技!\n");
    if((int)me->query_skill("force",1) < 100 )
        return 
        notify_fail("你內功修為不夠，不能使用拈花拂穴!\n");
    if((int)me->query_skill("finger") < 120 || me->query_skill("gekong",1) < 100 )
        return 
        notify_fail("你的指法修為不夠,目前還不能使用拈花拂穴絕技!\n");
    if( query("neili", me)<300 )
        return notify_fail("你的內力不夠, 不能使用拈花拂穴! \n");
    if( target->is_busy() )
        return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧，yeah\n");

    message("vision", CYN "你似乎聽到一聲似有似無的“嗤嗤”的聲音！\n\n" NOR, environment(me), ({me}) );
    tell_object(me, "你使出隔空點穴絕招，暗運內力，指端射出一股勁氣直點"+target->name()+"的要穴！\n\n" NOR);
if (!wizardp(me)) 
{
 if( random(query("combat_exp", me))>query("combat_exp", target)/4 )
    {
        tell_object(target, HIW "你突然間覺得渾身上下不聽使喚，動彈不得！\n" NOR);
        message("vision", CYN "只見"+target->name()+"突然間神色大變，動彈不得！\n\n" NOR, environment(me), ({target}) );
  busy_time=random( (int)me->query_skill("gekong",1) / 1 )+1;
        target->start_busy( busy_time );
        addn("neili", -100, me);
    }
    else
    {
    message("vision", CYN + target->name() + "好象突然覺得有一股勁氣向自己的要穴射了過來，不及細想閃了一閃。\n" NOR,environment(me),({target}));
    tell_object(target, CYN "你好象突然覺得有一股勁氣向自己的要穴射了過來，不及細想閃了一閃。\n" NOR);
    message_vision(CYN "$n從勁氣來向看到原來是$N在點自己的穴位，不禁大怒：敢暗算我，看招！\n" NOR,me,target);
//  if (target->query("shen") < -100 ) target->kill_ob(me);
target->fight_ob(me);
    me->fight_ob(target);
    me->start_busy(3);
    }
    set_temp("perform_time", time(), me);
    return 1;
}
else
{
 if( random(query("combat_exp", me))>query("combat_exp", target)/400 )
    {
        tell_object(target, HIW "你突然間覺得渾身上下不聽使喚，動彈不得！\n" NOR);
        message("vision", CYN "只見"+target->name()+"突然間神色大變，動彈不得！\n\n" NOR, environment(me), ({target}) );
  busy_time=random( (int)me->query_skill("gekong",1) / 2 )+1;
        target->start_busy( busy_time );
        addn("neili", -100, me);
    }
    else
    {
    message("vision", CYN + target->name() + "好象突然覺得有一股勁氣向自己的要穴射了過來，不及細想閃了一閃。\n" NOR,environment(me),({target}));
    tell_object(target, CYN "你好象突然覺得有一股勁氣向自己的要穴射了過來，不及細想閃了一閃。\n" NOR);
    message_vision(CYN "$n從勁氣來向看到原來是$N在點自己的穴位，不禁大怒：敢暗算我，看招！\n" NOR,me,target);
//  if (target->query("shen") < -100 ) target->kill_ob(me);
target->fight_ob(me);
    me->fight_ob(target);
       }
    set_temp("perform_time", time(), me);
    return 1;
}
}
