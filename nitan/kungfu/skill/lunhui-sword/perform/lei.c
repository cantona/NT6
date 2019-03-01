#include <ansi.h>
#include <combat.h>

string name() { return HIB "劍閃驚雷" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage,ran, ndam;
        string sexs;

        if (! target) target = offensive_target(me);
        
        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+ "只能在戰鬥中對對手使用。\n");
        
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" +name()+ "。\n");
        
        if (me->query_skill("lunhui-sword", 1) < 1200)
                return notify_fail("你的六道輪回劍修為不夠，難以施展" +name()+ "。\n");
        
        if (me->query_skill_mapped("sword") != "lunhui-sword")
                return notify_fail("你沒有激發六道輪回劍，難以施展" +name()+ "。\n");
        
        if (me->query_skill_mapped("sword") != "lunhui-sword")
                return notify_fail("你沒有激發六道輪回劍，難以施展" +name()+ "。\n");
        
        if( query("neili", me)<3000 )
                return notify_fail("你的真氣不夠，難以施展" +name()+ "。\n");
        
        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");
        
        msg = HIC "$N" HIC "輕嘯一聲，手中" + weapon->name() + HIC "平平一劍刺出，速度之快，有如電閃雷鳴一般！\n" NOR;
        
        ap=me->query_skill("sword")+query("force", me)+me->query_skill("martial-cognize",1);
        dp=target->query_skill("parry")+query("force", target)+target->query_skill("martial-cognize",1);
        
        if (1)
        {
                damage = ap / 4 + random(ap / 3);
                //damage += weapon->apply_damage(); // 追加一次武器的傷害
                addn("neili", -3000, me);
                me->start_busy(3);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 75,
                                           HIR "只聽$n" HIR "一聲慘叫，$N" HIR +
                                           weapon->name() + HIR "劍過之處，一道藍色電光射"
                                           "入$p" HIR "體內。\n"
                                           NOR);
                
                // 追加一次武器傷害
                ran = 35;
                ndam = 10;
                if (me->query_skill("lunhui-sword", 1) >= 5000)
                {
                        ran = 100;
                        ndam = 5;
                }
                else if (me->query_skill("lunhui-sword", 1) >= 4000)
                {
                        ndam = 7;
                }
                else if (me->query_skill("lunhui-sword", 1) >= 3000)
                {
                        ran = 75;
                }
                else if (me->query_skill("lunhui-sword", 1) >= 2000)
                {
                        ran = 50;
                }
                // 追加一次武器傷害
                if (random(100) < ran || wizardp(me))
                {
                        msg = msg + HIG + weapon->name() + HIG "發出雷鳴般的響聲，伴隨著一道劍光再次穿透" +
                              target->name() + HIG "身體……\n" NOR +
                              HIR "一股鮮血順著" + weapon->name() + HIR "噴射而出！\n" NOR;
                        target->receive_damage("qi", weapon->apply_damage() / 2, me);
                        target->receive_wound("qi", weapon->apply_damage() / 2, me);
                }
        
                if( !query_temp("lunhui-sword/jinglei", target) )
                {
                        // 第一次直接10%最大氣血傷害
                        target->receive_damage("qi",query("max_qi", target)/ndam,me);
                        target->receive_wound("qi",query("max_qi", target)/ndam,me);
                        msg = msg + target->name() +  HIM "悶哼一聲，鮮血噴出，看來是受到了這一劍的劍氣所傷。\n" NOR;
                        set_temp("lunhui-sword/jinglei", 1, target);
                }
        } else
        {
                addn("neili", -1000, me);
                me->start_busy(4);
                msg += CYN "$n" CYN "見$P" CYN "來勢洶湧，不敢輕易抵"
                       "擋，連忙飛身騰挪，躲閃開來。\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);
        
        return 1;
}

