// lunhui.c 六道杖法絕招：輪迴罔生
// By Alf, Last Update 2001.10

#include <ansi.h>

int perform(object me, object target)
{
    object weapon;
        string msg;
    int damage,sk1,sk2,exp1,exp2,stf;

    if( !target || !target->is_character() || !me->is_fighting(target) )
        return notify_fail("「輪迴罔生」只能對戰鬥中的對手使用。\n");

    sk1 = (int)me->query_skill("staff");
    if(target->query_skill_mapped("parry")==target->query_attack_skill())
        sk2 = ((int)target->query_skill("parry")+(int)target->query_skill("dodge"))/2;
    else
        sk2 = ((int)target->query_skill("parry",1)+(int)target->query_skill("dodge"))/2;
    exp1=query("combat_exp", me);
    exp2=query("combat_exp", target);
    stf = (int)me->query_skill("liudao-zhang",1);
        
    if( !objectp(weapon=query_temp("weapon", me) )
     || query("skill_type", weapon) != "staff" )
        return notify_fail("你使用的武器不對。\n");
                
    if(stf < 100 )
        return notify_fail("你的六道杖法不夠嫻熟，無法使出「輪迴罔生」。\n");
                                
     if( query("neili", me)<300 )
        return notify_fail("你現在內力太弱，不能使用「輪迴罔生」。\n");

    msg = 
HIY"$N突然冷哼一聲，手腕一挺，勁氣貫處，"+weapon->name()+HIY"去勢如箭，向$n當胸疾刺！\n"NOR;

    if (random(sk1*sk1*sk1/1000+exp1/100) > (sk2*sk2*sk2/2000+exp2/200) || !living(target))
    {
        if(stf<300)
            target->start_busy( stf / 40 + random(2));
        else
            target->start_busy(4);
                
        damage = (int)me->query_skill("liudao-zhang", 1);
        damage = damage +  stf;
        damage = damage +  (int)me->query_skill("stf", 1);

        target->receive_damage("qi", damage*1/2,me);
        target->receive_wound("qi", damage/3,me);
        addn("neili", -400, me);
        me->start_busy(3);
        msg += HIM"$n只覺後背一涼，胸前被"+weapon->name()+HIM"刺了個對穿，不由長聲慘呼！\n"NOR;
    }

    else
    {
        msg += YEL"可是$n早有防備，身形閃處，將$N的這一擊輕易化解。\n"NOR;
        addn("neili", -100, me);
        me->start_busy(4);
    }

    message_vision(msg, me, target);
        if(!userp(target) && !target->is_killing(query("id",me)) ) target->kill_ob(me); 
    return 1;
}
