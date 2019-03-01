// dan.c 亡月

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
                return notify_fail("「亡月」只能對戰鬥中的對手使用。\n");
 
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("運用「亡月」手中必須有劍！\n");

        if ((int)me->query_skill("canyue-sword", 1) < 200)
                return notify_fail("你的殘月劍法不夠嫻熟，不會使用「亡月」。\n");
                                
        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的內功修為不夠高。\n");
                        
        if( query("neili", me)<800 )
                return notify_fail("你現在內力太弱，不能使用「亡月」。\n");
                        
        msg = WHT "\n$N" WHT "劍尖忽然起了奇異的震動。劍尖本來是斜斜指向$n" WHT "，震動一起，萬物忽然間全都靜止。\n"
              "就連周圍的空氣，都彷佛也已停頓。\n" WHT "沒有任何言語可以形容這種情況，只有一個字，一個很簡單的字...\n\n"
              HIR "死！ \n\n" HIB "流水乾枯，變化窮盡，生命終結，萬物滅亡！\n\n" NOR; 

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

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -damage/2, me);

                msg += HIR "$N" HIR "手中的" + weapon->name() + HIR "似乎蘇醒過來，$n的生命卻在逐漸流逝，一切已無法再改變。 \n" NOR;
                
                target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/2 + random(damage/2),me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                
                target->start_busy(1+random(2));
                me->start_busy(3+random(2));
               
        } else 
        {
                msg += HIR "$N" HIR "一劍失去目標，忽然覺得靈魂仿佛被抽入" + weapon->name() + RED "再也無法控制！"
                       + weapon->name() + HIR "差點脫手而出！\n" NOR; 

                addn("neili", -100, me);
                me->start_busy(3);
                if (target->is_busy())
                        target->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}