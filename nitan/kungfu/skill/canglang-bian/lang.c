// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit F_SSERVER;
string name() { return "巨浪滔天"; }

int perform(object me, object target)
{
        object weapon;
        int skill;

        if (! target) target = offensive_target(me);

        if (! target
        ||      ! target->is_character()
        ||      ! me->is_fighting(target))
                return notify_fail("「巨浪滔天」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
        ||      query("skill_type", weapon) != "whip" )
                return notify_fail("你沒有鞭在手，施不出「巨浪滔天」。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的內力不夠！\n");

        if (me->query_skill("canglang-bian", 1) < 200)
                return notify_fail("你的「滄浪鞭法 」未臻高妙境界，無法施出「巨浪滔天」！\n");

        if (me->query_skill("bibo-shengong", 1) < 200)
                return notify_fail("你的碧濤玄功修為不夠，無法施出「滄浪鞭法」！\n");

        if (me->query_skill_mapped("whip") != "canglang-bian")
                return notify_fail("你所用的並非「滄浪鞭法 」，施展不出「巨浪滔天」！\n");

        message_combatd(
                HIR"$N忽然將"+(query("name", query_temp("weapon", me)))+
                HIR"頻頻甩出，"+(query("name", query_temp("weapon", me)))+
                HIR "發出劈啪暴空之聲不絕擾得$n心煩意亂。\n" NOR, me, target);
        message_combatd(
                HIB "$N的招數萬千，但鞭頭卻總是指向$n的周身要穴，攻擊如巨浪連綿無窮無盡，"
                "令$n只有招架之功卻無還手之力。\n" NOR, me, target);

        set_temp("julang", 1, me);

        skill =  ( me->query_skill("canglang-bian") + me->query_skill("dodge") ) / 2;

        addn_temp("apply/attack", skill/3, me);
        addn_temp("apply/defense", skill/3, me);

        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));

        addn("neili", -200, me);
        me->start_busy(random(2));

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill/3 :), skill/3);

        return 1;
}

private int remove_effect(object me, int amount)
{
        if( query_temp("julang", me) )
        {
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/defense", -amount, me);
                delete_temp("julang", me);
                message_combatd(YEL "\n$N慢慢內運內功，把真氣壓下！\n\n" NOR, me);
        }

        return 0;
}