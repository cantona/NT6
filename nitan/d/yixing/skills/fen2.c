// /kungfu/skill/huoyan-dao/fen.c
// /d/yixing/skills/fen.c perform 焚
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
#include <armor.h>
inherit F_SSERVER;
int perform(object me, object target)
{
        object armor;
        int damage;
        string *limb, type, result, str;

        type = "內傷";

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("你不在戰鬥中。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你不是空手。\n");

/*
        if( target->is_busy() )
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");
*/
        
        if( (int)me->query_skill("huoyan-dao", 1) < 120 )
                return notify_fail("你的火燄刀修為不夠。\n");
        if ( me->query_skill_mapped("force") != "xiaowuxiang" &&
                me->query_skill_mapped("force") != "longxiang-banruo")
                return notify_fail("你所用內功不對！\n");
        if( query("neili", me) <= 500 )
                return notify_fail("你的內力不夠！\n");
        message_vision(HIR "$N長吸一口氣，身上衣衫緩緩漲起，兩掌變得通紅，射出一股灼人熱氣。$n的身影被籠罩在一團火燄之中。\n\n" NOR, me,target);
//        tell_object(target, BLU "你只覺一股熱浪撲面，霍的胸口一陣劇痛。\n"NOR);
        addn("neili", -100, me);

        if( random(query("combat_exp", me))>query("combat_exp", target)/2 )
        {
                if( query_temp("armor/cloth", target) )
                {
                        armor=query_temp("armor/cloth", target);
                        if( query("armor_prop/armor", armor)<150 )
                        {
                                message_vision(HIY"只見$N身上的$n"+HIY+"已被震得粉碎，變成一塊塊破布掉在地上。\n"NOR, target, armor);
                                armor->unequip();
                                armor->move(environment(target));
                                set("name", "破碎的"+query("name", armor), armor);
                                set("value", 0, armor);
                                set("armor_prop/armor", 0, armor);
                                target->reset_action();
                        }
                }
                damage = random((int)me->query_skill("strike"))*5;
                target->receive_damage("qi", damage, me); 
                target->receive_wound("qi", (int)me->query_skill("huoyan-dao", 1), me);
                target->start_busy(1+random(3));
                
                limb=query("limbs", target);
                result = COMBAT_D->damage_msg(damage, type);
                result = replace_string( result, "$l", limb[random(sizeof(limb))]);
                result = replace_string( result, "$p", target->name() );
                message_vision(result, me, target);

                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                message_vision("($N"+str+")\n", target);
        }
        else 
        {
                message_vision(HIY "$p趕緊向後躍開數丈，躲開$P的攻擊。\n" NOR, me, target);
        }
        me->start_busy(1+random(3));
        return 1;
}