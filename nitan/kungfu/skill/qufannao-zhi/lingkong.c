// lingkong

#include <ansi.h>

inherit F_SSERVER;

#define LING "「" HIW "凌空指穴" NOR "」" 

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if( userp(me) && !query("can_perform/qufannao-zhi/lingkong", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");   

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail(LING "只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能使用" LING "！\n");           

        if( (int)me->query_skill("qufannao-zhi", 1) < 120 )
                return notify_fail("你的去煩惱指不夠嫻熟，不會使用" LING "。\n");

        if( (int)me->query_skill("hunyuan-yiqi", 1) < 100 )
                return notify_fail("你的心意氣混元功不夠高，不能用內力催動指力傷敵。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在內力太弱，不能使用" LING "。\n");

        msg = CYN "$N默念佛經，只見手指微動，幾道指氣急射向$n，意欲以指力擊暈$n。\n"NOR;

        ap = me->query_skill("force", 1) + me->query_skill("finger", 1) + 
             me->query_skill("qufannao-zhi",1)+query("neili", me)/50;
        dp = target->query_skill("force", 1) + target->query_skill("dodge", 1) +
             target->query_skill("parry", 1);
        if (random(ap) + random(ap / 3) > dp )
        {
                me->start_busy(3);
                target->start_busy(random(3));
                
                damage = (int)me->query_skill("qufannao-zhi", 1);
                
                damage = damage / 3 + random(damage / 3);
                
                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage / 6);
                addn("neili", -damage/6, me);
                
                if( damage < 20 )
                        msg += HIY "$n受到$N的指力透擊，悶哼一聲，看上去很是疲憊。\n" NOR;
                
                else if( damage < 40 )
                        msg += HIY "$n被$N的指力反擊，只覺得胸中煩悶，只想好好休息休息。\n" NOR;
        
                else if( damage < 80 )
                        msg += RED "$n被$N以指力一震，腦中嗡嗡作響，意識開始模糊起來！\n" NOR;
                else
                        msg += HIR "$n被$N的指力一震，眼前一黑，向後便倒，眼看就要不醒人事了！\n" NOR;
                
        }
        else 
        {
                me->start_busy(4);
                msg += CYN "可是$p看破了$P的企圖，並沒有上當。\n" NOR;
        }
        message_vision(msg, me, target);

        return 1;
}
