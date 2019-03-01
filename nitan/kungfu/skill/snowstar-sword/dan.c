// dan.c 劍氣無雙

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon,weapon2;
        int damage,i;
        string msg,str;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        
        if (! target || ! me->is_fighting(target))
                return notify_fail("「劍氣無雙」只能對戰鬥中的對手使用。\n");
 
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("運用「劍氣無雙」手中必須有劍！\n");

        if ((int)me->query_skill("snowstar-sword", 1) < 200)
                return notify_fail("你的雪影寒星劍法不夠嫻熟，不會使用「劍氣無雙」。\n");
                                
        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的內功修為不夠高。\n");
                        
        if( query("neili", me)<800 )
                return notify_fail("你現在內力太弱，不能使用「劍氣無雙」。\n");
                        
        msg = HIW "\n$N" HIW "靈台清明，身隨意走，劍氣如虹，手中" + weapon->name() + HIW "激起一道如匹練般的劍光，毫無花哨的刺向$n" HIW "。\n\n" NOR;

        ap = me->query_skill("sword") + me->query_skill("force");
        ap+=query("jiali", me);
        ap+=query("jianu", me);
        
        damage = ap*2 + random(ap);
        damage+=query("jiali", me);

        if (living(target))
                dp = target->query_skill("dodge",1) + target->query_skill("parry",1);
        else
                dp = 0;

        dp = dp*3/2;

        weapon2=query_temp("weapon", target);

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -damage/2, me);

                if (weapon2)
                {
                        msg += HIR "\n$n" HIR "見$N" HIR "來勢兇猛，匆忙抵擋下，手中" + weapon2->name() + HIR "被震成幾截，斷裂當場！\n" NOR;
                        damage -= damage/3;
                        weapon2->set_name("碎裂的"+query("name", weapon2));
                        weapon2->move(environment(target));
                        set("value", 0, weapon2);
                        set("weapon_prop", 0, weapon2);
                        target->reset_action();
                }
                msg += HIR "$n" HIR "面對這大巧若拙的一劍，頓時呆立當場，眼睜睜看著" + weapon->name() + HIR "從自己的胸口穿過，目光中透出一種不可思議的神色。\n" NOR;
                
                target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/2 + random(damage/2),me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                
                target->start_busy(1+random(2));
                me->start_busy(3+random(2));
               
        } else 
        {
                msg += HIR "$n" HIR "急忙左右跳躍，終于脫出了劍光的包圍。\n" NOR;

                addn("neili", -100, me);
                me->start_busy(3);
                if (target->is_busy())
                        target->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}