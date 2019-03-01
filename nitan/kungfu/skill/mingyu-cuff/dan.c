// dan.c 亢龍無悔

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
                return notify_fail("「亢龍無悔」只能對戰鬥中的對手使用。\n");
 
        if(me->query_skill_mapped("cuff") != "mingyu-cuff") 
                return notify_fail("你沒有用明玉拳，無法使用「亢龍無悔」絕招！\n");

        if (me->query_skill_prepared("cuff") != "mingyu-cuff")
                return notify_fail("你沒有準備使用明玉拳，無法施展「亢龍無悔」絕招。\n");

        if( objectp(weapon=query_temp("weapon", me)) || 
            objectp(weapon=query_temp("handing", me)) )
                return notify_fail("你必須空著雙手才能使用掌法絕招。\n");

        if ((int)me->query_skill("mingyu-cuff", 1) < 200)
                return notify_fail("你的明玉拳不夠嫻熟，不會使用「亢龍無悔」。\n");
                                
        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的內功修為不夠高。\n");
                        
        if( query("neili", me)<800 )
                return notify_fail("你現在內力太弱，不能使用「亢龍無悔」。\n");
                        
        msg = HIB "\n$N" HIB "把全身勁力運于雙拳，一聲大喝，平平地向$n推出雙掌！\n" NOR;

        ap = me->query_skill("cuff") + me->query_skill("force");
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
        
        if (ap / 3 + random(ap/2) > dp)
        {
                damage += damage/2;
                addn("neili", -damage/2, me);

                msg += HIR "\n只聽見啪的一聲巨響，$N" HIR "的雙拳已經紮紮實實的打在$n" HIR "身上了！\n" NOR;
                target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/2 + random(damage/2),me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                
                target->start_busy(1+random(2));
                me->start_busy(3+random(2));
        } else if (ap / 2 + random(ap) > dp)
        {
                damage += damage/2;
                addn("neili", -damage/2, me);

                if (weapon2)
                {
                        msg += HIM "\n$n" HIM "避無可避，只好舉起手中的" NOR + weapon2->name() + HIM "硬擋一招。\n"
                               HIM "只聽“啪”的一聲，$n" HIM "的" NOR + weapon2->name() + HIM "已經被打成兩截。\n" NOR;
                        if (ap / 3 + random(ap) > dp)
                        {
                                damage -= damage/3;
                                msg += HIM "$N" HIM "拳勢頓得一頓，卻依然重重地打在了$n" HIM "身上。\n" NOR;
                        } else
                        {
                                damage -= damage/2;
                                msg += HIM "$n" HIM "雖然兵器被打斷，卻也緩了口氣，乘機避開。\n" NOR;
                        }
                        weapon2->set_name("斷裂的"+query("name", weapon2));
                        weapon2->move(environment(target));
                        set("value", 0, weapon2);
                        set("weapon_prop", 0, weapon2);
                        target->reset_action();
                } else
                {
                        msg += HIG "\n$n" HIG "避無可避，只好也同樣雙拳平推硬擋一招。\n"
                               HIG "一聲驚天動地地巨響，雙拳相交之下，$n" HIG "被震地氣血翻湧。\n" NOR;
                        if (ap / 2 + random(ap) > dp)
                        {
                               msg += HIG "$N" HIG "的拳勁絲毫不受影響，依然重重的打在了$n" HIG "的身上！\n" NOR;
                        } else if (ap / 2 + random(ap*2) > dp)
                        {
                               msg += HIG "$n" HIG "雖然擋開了$N" HIG "的雷霆一擊，卻仍然被拳風所傷，只覺一陣窒息。\n" NOR;
                               damage -= damage/3;
                        } else
                        {
                               msg += HIG "兩人拳勁相交之下，$N" HIG "的全力一擊被完全化解。\n" NOR;
                               damage -= damage; 
                        }

                }               
                target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/2 + random(damage/2),me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                
                target->start_busy(1+random(2));
                me->start_busy(3+random(2));
        } else
        {
                if (weapon2)
                        msg += HIY "$n" HIY "以四兩撥千斤之法，隨意揮動" NOR + weapon2->name() + HIY "，便撥開了$N" HIY "的"HIR"亢龍無悔。\n" NOR;
                else
                        msg += HIY "$n" HIY "以四兩撥千斤之法，隨意揮手，便撥開了$N" HIY "的"HIR"亢龍無悔。\n" NOR;

                addn("neili", -100, me);
                me->start_busy(3);
                if (target->is_busy())
                        target->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}