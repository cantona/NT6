// linglong.c 玉玲瓏

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
                return notify_fail("「玉玲瓏」只能對戰鬥中的對手使用。\n");
 
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("運用「玉玲瓏」手中必須有劍！\n");

        if ((int)me->query_skill("liudaolunhui-sword", 1) < 200)
                return notify_fail("你的六道輪回劍法不夠嫻熟，不會使用「玉玲瓏」。\n");
                                
        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的內功修為不夠高。\n");
                        
        if( query("neili", me)<800 )
                return notify_fail("你現在內力太弱，不能使用「玉玲瓏」。\n");
                        
        msg = HIW "\n$N" HIW "身影慢慢的浮現在$n" HIW "面前，只見$N" HIW "洒出無數晶瑩剔透的"
              "玉玲瓏圍繞在$n" HIW "周圍。\n刀光劍影的世界霎時間沉寂在這柔和的雪光之中，"
              "好一記溫柔纏綿的玉玲瓏\n\n" HIM "縱情山水間，揮洒天地情!\n\n" NOR;

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

                msg += HIW "$n" HIW "頓時沉寂在這夢一般的景象之中，如痴如醉中被雪玲瓏擊中了!\n"
                       "$n" HIW "完全陷入玉玲瓏的威力之中無法自拔。\n看著劍光從前心穿過" NOR;
                
                if( objectp(weapon2=query_temp("weapon", target)) )
                {
                        msg += HIW "，手中" + weapon2->name() + HIW "當啷一聲掉在地上。\n" NOR;
                        weapon2->move(environment(target));
                }
                else
                        msg += HIW "。\n" NOR;

                target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/2 + random(damage/2),me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                
                target->start_busy(1+random(2));
                me->start_busy(3+random(2));
               
        } else 
        {
                msg += HIY "可$n" HIY "並沒有被這絢麗的雪景所吸引,依然屹立在雪花飛舞的幻景中！\n" NOR;

                addn("neili", -100, me);
                me->start_busy(3);
                if (target->is_busy())
                        target->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}