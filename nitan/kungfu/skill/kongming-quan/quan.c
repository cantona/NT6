
#include <ansi.h>

inherit F_SSERVER;

string name() { return "亂拳飛舞"; }

int perform(object me, object target)
{
        object weapon;
        int damage,skill,wap,wdp;
        string *limb, type, result, str,msg;

        type = "內傷";

        if( !target ) target = offensive_target(me);

        if( !target
        ||        !target->is_character()
        ||        !me->is_fighting(target) )
                return notify_fail("亂拳飛舞只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("空手才能施展亂拳飛舞！\n");

        if( me->query_skill_mapped("unarmed") != "kongming-quan" )
                return notify_fail("你所用的並非空明拳，不能施展亂拳飛舞！\n");

        if( me->query_skill_prepared("unarmed") != "kongming-quan" )
                return notify_fail("你所備的並非空明拳，不能施展亂拳飛舞！\n");

        /*
        if( me->query_skill_mapped("force") != "xiantian-gong" )
                return notify_fail("你所用的並非先天功，施展不出亂拳飛舞！\n");
        */

        if( me->query_skill("force") < 120 )
                return notify_fail("你的先天功火候未到，無法施展亂拳飛舞！\n");

        if( me->query_skill("unarmed") < 120 )
                return notify_fail("亂拳飛舞需要精湛的空明拳方能有效施展！\n");

        if( query("max_neili", me) <= 1000 )
                return notify_fail("你的內力等級不夠使用亂拳飛舞！\n");

        if( query("neili", me) <= 1000 )
                return notify_fail("你的內力不夠，無法繼續施展亂拳飛舞！\n");

        msg = HIY"$N張口一聲暴喝，雙目精光四射，接着身形飄忽不定，雙拳幻化出漫天拳影重重向$n籠罩過去！\n\n"NOR;
        message_combatd(msg, me, target);

        skill =  me->query_skill("unarmed");

        addn_temp("apply/unarmed_damage", skill/2, me);
        addn_temp("apply/attack", skill/2, me);

        message("vission",HIR  "上一拳！\n" NOR,environment(me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        message("vission",HIR  "下一拳！\n" NOR,environment(me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        message("vission",HIR  "左一拳！\n" NOR,environment(me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        message("vission",HIR  "右一拳！\n" NOR,environment(me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        message("vission",HIR  "前一拳！\n" NOR,environment(me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        message("vission",HIR  "後一拳！\n" NOR,environment(me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        message("vission",HIR  "最後再一拳！\n" NOR,environment(me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        me->start_busy(3);

        addn_temp("apply/unarmed_damage", -skill/2, me);
        addn_temp("apply/attack", -skill/2, me);

        addn("neili", -skill, me);

        return 1;
}