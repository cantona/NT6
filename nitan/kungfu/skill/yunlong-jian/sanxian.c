#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int i,lvl;
        
        if( !target ) target = offensive_target(me);

        if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        || !living(target))
                return notify_fail("「雲龍三現」只能對戰鬥中的對手使用。\n");

        if( (int)me->query_skill("yunlong-jian", 1) < 120 )
                return notify_fail("你的雲龍劍法功力太淺，別做夢了。\n");

        if( (int)me->query_skill("sword", 1) < 120 )
                return notify_fail("你的基本劍法功力太淺，別做夢了。\n");
                        
        if( query("max_neili", me)<1200 )
                return notify_fail("你的內力太淺，別做夢了。\n");
                
        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠，別做夢了。\n");
                
        if( me->query_skill_mapped("force") != "yunlong-shengong" &&
            me->query_skill_mapped("force") != "jiuyang-shengong") 
            
                return notify_fail("你用什麼為基礎來使雲龍劍絕技麼?\n");
        if( !(weapon=query_temp("weapon", me)) || query("skill_type", weapon) != "sword"
            || me->query_skill_mapped("sword") != "yunlong-jian")
                return notify_fail("你使得了雲龍劍絕技麼?\n");
                
        lvl = ( (int)me->query_skill("yunlong-jian", 1) + (int)me->query_skill("force", 1) ) /8;
        
        addn("neili", -300, me);
        message_combatd(HIR "\n$N長笑一聲，隨手一抖，" + weapon->name() + HIR"竟嗡嗡作響，宛若龍吟一般。\n"
                "突然間劍光一閃，旁人只聽“哧哧”幾聲輕響， $N已在一瞬間向$n刺了三劍，快的異乎尋常！\n"NOR, 
                me, target);
                
        addn_temp("apply/dex", lvl, me);
        addn_temp("apply/damage", lvl, me);
        addn_temp("apply/str", lvl, me);
        addn_temp("apply/attack", lvl, me);
        
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),2);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);
        
        addn_temp("apply/damage", -lvl, me);
        addn_temp("apply/str", -lvl, me);
        addn_temp("apply/dex", -lvl, me);
        addn_temp("apply/attack", -lvl, me);
        
        me->start_busy(3);
        return 1;
}
