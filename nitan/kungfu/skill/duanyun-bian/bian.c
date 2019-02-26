
#include <ansi.h>

inherit F_SSERVER;
string name() { return "風雲變色"; }

int perform(object me, object target)
{
        int skill,power;
        string weapon;

        if( !target ) target = offensive_target(me);

        if( !target
        ||        !target->is_character()
        ||        !me->is_fighting(target) )
                return notify_fail("風雲變色只能對戰鬥中的對手使用。\n");


         /*
        if( me->query_skill_mapped("force") != "xiantian-gong" )
                 return notify_fail("你所用的並非玄門先天功，施展不出風雲變色！\n");
         */

        if( me->query_skill("force") < 140 )
                return notify_fail("你的基本內功火候未到，無法施展風雲變色！\n");

        if( me->query_skill("whip") < 135 )
                return notify_fail("風雲變色需要精湛的斷雲鞭法方能有效施展！\n");

        if( !query_temp("weapon", me) || query("skill_type", query_temp("weapon", me)) != "whip" )
                return notify_fail("你並沒有裝備鞭作為武器。\n");

        power=random(query("neili", me)/50)+query("jiali", me)/2;
        if(power<150) power=150;
        if(power>1000) power=1000;

        if( query("neili", me) <= 200+power*2 )
                return notify_fail("你的內力不夠使用風雲變色！\n");

        message_combatd(HIW"$N運足內力，猛地一揚"NOR+"$n"+HIW"捲起無邊風雲遮月掩日，一股"NOR+HIM"罡風"NOR+HIW"隨著漫天鞭影撲天蓋地的向敵人襲來。\n\n"NOR,me,query_temp("weapon", me));

        addn_temp("apply/attack", power/2, me);
        addn_temp("apply/damage", power/5, me);
        addn_temp("apply/armor", -power/2, target);
        addn_temp("apply/dodge", -power, target);

        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));

        addn_temp("apply/attack", -power/2, me);
        addn_temp("apply/damage", -power/5, me);
        addn_temp("apply/armor", power/2, target);
        addn_temp("apply/dodge", power, target);

        addn("neili", -power*2, me);
        me->start_busy( 2+random(2));

        return 1;
}

