 // 修羅降世 xiuluo.c

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "修羅降世"; }

int perform(object me, object target)
{
      object weapon;

      int i, jiali;
      string msg;

       if( !target ) target = offensive_target(me);
       if( !target
        || !target->is_character()
        || !me->is_fighting(target)
        || !living(target))
                return notify_fail("「修羅降世」攻擊只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) )
                return notify_fail("「修羅降世」是空手絕技，你拿着武器是使不出來的！\n");

        if ( me->query_skill_mapped("strike") != "huoyan-dao")
                return notify_fail("你必須使用火焰刀來施展「修羅降世」。\n");

        if(me->query_skill("huoyan-dao", 1) < 150 )
                return notify_fail("你的火焰刀火候還嫌不夠，這「修羅降世」絕技不用也罷。\n");

        if(me->query_skill("strike", 1) < 150 )
                return notify_fail("你的基本掌法還不夠嫻熟，使不出「修羅降世」絕技。\n");

        if(userp(me) && (int)me->query_skill("xiaowuxiang", 1) < 100 )
                return notify_fail("你的小無相功等級不夠高，使不出「修羅降世」。\n");

       if( query("max_neili", me)<2000 )
           return notify_fail("你的內力修為不夠，這「修羅降世」絕技不用也罷。\n");

       if( query("neili", me)<500 )
           return notify_fail("以你目前的內力來看，這「修羅降世」絕技不用也罷。\n");

       if( query("jing", me)<80 )
           return notify_fail("你的精力不夠。\n");



        addn("jing", -20, me);
        msg =HIR "突然" HIR "$N" HIR "雙掌搓了幾搓，只聽得嗤嗤聲響，「火焰刀」在" HIR "$N" HIR "極強內勁的斗然衝擊之下\n"
             HIR "威勢大盛，激射而出的無形刀氣組成了一片刀網，宛如修羅降世，向着" HIR "$n" HIR "直劈而下! \n" NOR;

        message_combatd(msg,me,target);
        i = me->query_skill("force") / 4;
        jiali=query("jiali", me);

        set("jiali", i, me);
        addn_temp("apply/attack", jiali+200, me);
        addn_temp("apply/unarmed_damage", jiali+200, me);
        msg = HIY"\n\n刀山火海！\n\n"NOR;
        message_combatd(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);



        msg = HIR"------無盡煉獄！\n\n"NOR;
        message_combatd(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);



        msg = RED"--------------四方俱滅！\n\n"NOR;
        message_combatd(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);



        addn_temp("apply/attack", -jiali-200, me);
        addn_temp("apply/unarmed_damage", -jiali-200, me);
        me->start_busy(1+random(2));
        return 1;
}
