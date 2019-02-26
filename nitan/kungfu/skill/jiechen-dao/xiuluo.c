// by snowman

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
      int i, jiali, count;
        string msg;
       object weapon;

       if( !target ) target = offensive_target(me);
       if( !target
        || !target->is_character()
        || !me->is_fighting(target) 
        || !living(target))
                return notify_fail("「修羅焰」攻擊只能對戰鬥中的對手使用。\n");

      if( !objectp(weapon=query_temp("weapon", me)) || 
          query("skill_type", weapon) != "blade" )
                return notify_fail("你先找把刀再説吧！\n");


        if (me->query_skill_mapped("blade") != "jiechen-dao")
                return notify_fail("你必須使用戒塵刀來施展「修羅焰」。\n");

        if(me->query_skill("jiechen-dao", 1) < 180 )
                return notify_fail("你的戒塵刀火候還嫌不夠，這「修羅焰」絕技不用也罷。\n");

        if(me->query_skill("blade", 1) < 180 )
                return notify_fail("你的基本刀法還不夠嫻熟，使不出「修羅焰」絕技。\n");

        if( (int)me->query_skill("hunyuan-yiqi", 1) < 140 )
                return notify_fail("你的心意氣混元功等級不夠，使不出「修羅焰」絕技。\n");

        if( (int)me->query_con() < 34)
                return notify_fail("你的身體還不夠強壯，強使「修羅焰」絕技是引火自焚！\n");

        if ( me->query_skill_mapped("force") != "hunyuan-yiqi")
           return notify_fail("你現在這內功平平無奇，如何使得出「修羅焰」絕技來！？\n"); 

        if( query("max_neili", me)<3000 )
           return notify_fail("你的內力修為不夠，這「修羅焰」絕技不用也罷。\n");

        if( query("neili", me)<1000 )
           return notify_fail("以你目前的內力來看，這「修羅焰」絕技不用也罷。\n");

        addn("neili", -300, me);
 
        message_vision(HIR "\n突然$N將手中武器從右手交到左手，運出十二分真力，臉色頓時通紅，\n"
                           "宛如修羅降世。刀刃在內力的催動下立刻攻勢大勝，\n"
                           "向着$n直劈而下！\n" NOR, me, target);      

        i = me->query_skill("force") / 2 * (3+random(4));        
        jiali=query("jiali", me);

        set("jiali", i, me);
        addn_temp("apply/attack", jiali/2, me);
        
        count = 4;
        count += random(4);
        while (count --)
        {

              COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);
        }
        
        addn_temp("apply/attack", -jiali/2, me);
        set("jiali", jiali, me);
        if( !query_temp("xiuluo", me))addn("neili", -300, me);
        else delete_temp("xiuluo", me);

        me->start_busy(1+random(3));
        return 1;
}
