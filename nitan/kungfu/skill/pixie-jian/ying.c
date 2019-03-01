// ying.c 鬼影

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon;
        int i;
        int skill;
        int count;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( query("gender", me) != "無性" && !query("reborn/times", me) )
                return notify_fail("你的性別與日月內功相斥，無法使用此絕招！\n");  

        if( userp(me) && !query("can_perform/pixie-jian/ying", me) )
                return notify_fail("你還不會使用「鬼影」這一招。\n");

        if (! me->is_fighting(target))
                return notify_fail("「鬼影」只能對戰鬥中的對手使用。\n");

        skill = me->query_skill("pixie-jian", 1);

        if (skill < 120)
                return notify_fail("你的辟邪劍法修為有限，現在不能使用「鬼影」！\n");

        if( query("neili", me)<100 )
                return notify_fail("你的真氣不夠，無法運用「鬼影」！\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
           query("skill_type", weapon) != "sword" )
                return notify_fail("你只有裝備劍才能施展「鬼影」！\n");

        if( me->query_skill_mapped("sword") != "pixie-jian") 
                return notify_fail("你並沒有使用辟邪劍法，無法使用此絕招！\n"); 

        if (weapon)
        {
                msg = HIR "\n$N" HIR "冷笑一聲，如鬼魅般飄向$n，身法快得不可思議!"
                      HIR "手中的" + weapon->name() + HIR "或點，或刺，或劈，\n剎時間已向$n周身上下連攻數劍!\n\n"
                      HIC "$n根本無法看清劍招的來路，當下方寸大亂" HIC "!\n" NOR; 
       
      }

        message_combatd(msg, me, target);
        count = skill + me->query_skill("riyue-guanghua", 1);
        if( me->query_skill_mapped("force") != "riyue-guanghua")
        count /= 2;

        addn_temp("apply/attack", count, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 0 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        
        me->start_busy(2 + random(3));
        addn_temp("apply/attack", -count, me);
        
        return 1;
}
