// sanwu.c
// Xuanyuan 14/7/2001

#include <ansi.h>
inherit F_SSERVER;

void remove_effect(object me);

int perform(object me, object target)
{
        int skill, amount;
        string weapon;

        if( !target ) target = offensive_target(me);

               if( userp(me) && !query("can_perform/jueqing-bian/sanwu", me) )
                return notify_fail("你未經高人指點，雖聽過這「三無三不手」，卻不知怎樣施展。\n");

        if( query_temp("sanwu_busy", me) )
                return notify_fail("你微一運勁，卻發現自己雙臂痠軟，一時無法施展「三無三不手」！\n");

        if( !target || !target->is_character() ||  !me->is_fighting(target) )
                return notify_fail("「三無三不手」只能對戰鬥中的對手使用。\n");

        if( query_temp("yield", me) )
                return notify_fail("你不出掌，如何使出「三無三不手」？\n");

        if( me->query_skill_mapped("force") != "wudu-xinfa" )
                return notify_fail("你所用的內功與「三無三不手」氣路相悖！\n");

        if( me->query_skill("wudu-xinfa", 1) < 60 )
                return notify_fail("你的五毒心法火候未到，無法施展「三無三不手」！\n");

        if( me->query_skill("jueqing-bian", 1) < 100 )
                return notify_fail("絕情鞭法不夠嫻熟，無法施展「三無三不手」！\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力修為不夠，無力施展「三無三不手」！\n");

        if( query("neili", me)<800 )
                return notify_fail("你現在的內力太弱，不夠使用「三無三不手」！\n");

        if( query("jingli", me)<300 )
                return notify_fail("你現在的體力太弱，不夠使用「三無三不手」\n");

        message_vision( HIR"\n$N一聲冷笑，迅捷凌利的連攻三招，正是赤煉仙子的絕技「三無三不手」！\n"NOR, me);

        addn("neili", -400, me);
        addn("jingli", -100, me);
        set_temp("sanwu", 1, me);

                skill = me->query_skill("whip");

                switch(query_temp("sanwu", me) )
                {
                        case 1:         
                                amount = skill/20;
                                break;
                        case 2:
                                amount = skill/15;
                                break;
                        case 3:
                                amount = skill/10;
                                break;
                }

                addn_temp("apply/attack", amount, me);
                addn_temp("apply/damage", amount, me);

                COMBAT_D->do_attack(me,target,query_temp("weapon", me));
                addn_temp("sanwu", 1, me);
                COMBAT_D->do_attack(me,target,query_temp("weapon", me));
                addn_temp("sanwu", 1, me);
                COMBAT_D->do_attack(me,target,query_temp("weapon", me));
                addn_temp("sanwu", 1, me);
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/damage", -amount, me);

                set_temp("sanwu_busy",query_temp("sanwu",  me), me);

                if( !query_temp("sanwu", me) || query_temp("sanwu", me) == 4 )
                        remove_effect(me);

                me->start_busy(2);
                return 1;
}

void remove_effect(object me)
{
        int sanwu_busy=query_temp("sanwu_busy", me);

        int amount = (int)(450 - me->query_skill("whip")) / 2;
        if ( amount < 15 ) amount = 15;

        if ( sanwu_busy == 4 )
                message_vision(RED"\n$N三鞭擊出，三無三不發揮得淋漓盡致，端是毒辣至極。\n"NOR,me);

        // if 3 hit all missed, delete sanwu temp here.
        if( query_temp("sanwu", me) )
                delete_temp("sanwu", me);

        // more hits, cost more neili, min 100, max 300.
        addn("neili", -100*sanwu_busy, me);

        // more hits, longer busy time, longer to receive heal.
        me->start_busy(sanwu_busy + random(2));
        call_out("receive_heal", (int)amount * sanwu_busy / 3, me);
}

void receive_heal(object me)
{
        if ( !me ) return;

        delete_temp("sanwu_busy", me);
        tell_object(me, HIG"\n你經過一陣運功調息，臂上勁力盡復，隨時可以再以三無三不手攻敵。\n"NOR); 
}
