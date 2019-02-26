// dan.c 九字真言

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
                return notify_fail("「九字真言」只能對戰鬥中的對手使用。\n");
 
        if(me->query_skill_mapped("finger") != "nine-finger") 
                return notify_fail("你沒有用九字真言手印，無法使用「九字真言」絕招！\n");

        if (me->query_skill_prepared("finger") != "nine-finger")
                return notify_fail("你沒有準備使用九字真言手印，無法施展「九字真言」絕招。\n");

        if( objectp(weapon=query_temp("weapon", me)) || 
            objectp(weapon=query_temp("handing", me)) )
                return notify_fail("你必須空着雙手才能使用指法絕招。\n");

        if ((int)me->query_skill("nine-finger", 1) < 200)
                return notify_fail("你的九字真言手印不夠嫻熟，不會使用「九字真言」。\n");
                                
        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的內功修為不夠高。\n");
                        
        if( query("neili", me)<800 )
                return notify_fail("你現在內力太弱，不能使用「九字真言」。\n");
                        
        msg = HIM "\n$N" HIM "口中默誦九字真言，忽然招式一緩，身形急退，須臾已在丈許之外。\n"
              "$n" HIM "見$N" HIM "力有不繼，正要搶上反擊，卻見$N" HIM "雙手緊扣，拇指微伸，遙指$n" HIM "。 \n"
              "$n" HIM "一時亂了陣腳，不知$N" HIM "所出何招，心頭一陣迷惘。\n"
              "忽聞$N" HIM "一聲龍吟:\n"
              HIW " 臨 兵 鬥 者 皆 陣 列 在 前 !\n"
              HIM "喝聲中混雜着強勁的" + HIW + to_chinese(me->query_skill_mapped("force")) + HIM "，$n" HIM "不由心神大亂，\n"
              "只感到對方此拳充天塞地，螺旋真氣滔滔不絕從四面八方湧來，即使協生雙翼，還是避無可避！\n\n" NOR;

        ap = me->query_skill("finger") + me->query_skill("force");
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
                        msg += HIM "\n$n" HIM "見$N" HIM "來勢兇猛，不敢正面抵擋，手中" + weapon2->name() + HIM "滿天幻影，防得水泄不通\n"
                               HIM "$N" HIM "竟是置若罔聞，" HIW "螺旋勁氣" HIM "仍舊綿綿不絕，$n" HIM "手中" + weapon2->name() + HIM "在真氣激盪之下，\n"
                               HIM "化為寸許的二三十截，飛上半空，閃出點點白光！\n" NOR;
                                damage -= damage/3;
                                weapon2->set_name("碎裂的"+query("name", weapon2));
                                weapon2->move(environment(target));
                                set("value", 0, weapon2);
                                set("weapon_prop", 0, weapon2);
                                target->reset_action();
                } else
                        msg += HIM "\n$n" HIM "見$N" HIM "來勢兇猛，不敢正面抵擋，側身進步雙掌奮力側擊$N，\n"
                               "$N" HIM "竟是置若罔聞，" HIW "螺旋勁氣" HIM "仍舊綿綿不絕，$n" HIM "無可奈何之下，被擊個正着！\n" NOR;

                target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/2 + random(damage/2),me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                
                target->start_busy(1+random(2));
                me->start_busy(3+random(2));
        } else 
        {
                if (weapon2)
                        msg += HIM "\n$n" HIM "見$N" HIM "來勢兇猛，不敢正面抵擋，手中" + weapon2->name() + HIM "滿天幻影，防得水泄不通\n"
                               "$N" HIM "被緩得一緩，" HIW "螺旋勁氣" HIM "已然落空\n" NOR;
                else
                        msg += HIM "\n$n" HIM "見$N" HIM "來勢兇猛，不敢正面抵擋，側身進步雙掌奮力側擊$N，\n"
                               HIM "$N" HIM "被緩得一緩，" HIW "螺旋勁氣" MAG "已然落空，但$n" HIM "也被$N" HIM "震得氣血翻湧！\n" NOR;

                addn("neili", -100, me);
                me->start_busy(3);
                if (target->is_busy())
                        target->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}