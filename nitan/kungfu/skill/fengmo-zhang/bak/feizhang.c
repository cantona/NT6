//lianhuan.c  瘋魔杖法之瘋魔飛杖

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

void check_fight(object me, object target, object weapon);
private int remove_attack(object me, object weapon);

int perform(object me, object target)
{
        object weapon;
        int skill;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("瘋魔飛杖只能對戰鬥中的對手使用。\n");

        if( query_temp("fengmo", me) )
                return notify_fail("你已在使用瘋魔飛杖了！\n");

        weapon=query_temp("weapon", me);
        if( !objectp(weapon) || query("skill_type", weapon) != "staff" )
                return notify_fail("你手中無杖，如何能夠施展瘋魔飛杖？\n");

        if( me->query_skill_mapped("force") != "huntian-qigong" && me->query_skill_mapped("force") != "jiaohua-neigong"  )
                return notify_fail("你所用的內功不對，無法配合杖法施展瘋魔飛杖！\n");

        if( me->query_skill("force") < 100 )
                return notify_fail("你的內功火候未到，無法配合杖法施展瘋魔飛杖！\n");

        if( me->query_skill("staff") < 100 )
                return notify_fail("你瘋魔杖法修為不足，還不會使用瘋魔飛杖！\n");

        if( query("neili", me) <= 300 )
                return notify_fail("你的內力不夠施展瘋魔飛杖！\n");
        if( query("jingli", me) <= 200 )
                return notify_fail("你的精力不夠施展瘋魔飛杖！\n");

        skill = me->query_skill("staff");
        
        message_vision(HIR "\n$N大喝一聲將手中急轉著的"+weapon->name()+"脫手擲出，在空中高低左右回旋！\n\n" NOR, me, target);

        set_temp("fengmo", 1, me);
        set_temp("location", file_name(environment(me)), me);
        addn("neili", -200, me);
        addn("jingli", -100, me);
        weapon->unequip();
        set("no_clean_up", 1, weapon);
        me->reset_action();
        call_out("check_fight", 1, me, target, weapon);

        return 1;
}

void check_fight(object me, object target, object weapon)
{
        string *limbs, limb, result, str, type;
        int damage, dp;

        if ( !objectp( me ) ) return;
        me->reset_action();

        if( query_temp("fengmo", me) >= me->query_skill("fengmo-zhang",1)/5 || 
             !living(me) ||
             !me->is_fight(target) ||
             !query_temp("fengmo", me) )
        {
               call_out("remove_attack", 1, me, weapon);
        } else {
                limbs=query("limbs", target);
                limb = limbs[random(sizeof(limbs))];
                type = "挫傷";

                message_vision(HIR "\n突然間$n自行向$N的"+limb+"猛然飛撞過去！\n" NOR, target, weapon);

                if (living(target))
                        dp=query("combat_exp", target);
                else  dp = 0;
                if( random(query("combat_exp", me))>dp )
                {
                        //RYU: the following code is to make it look nice.
                        damage = 5+random(me->query_skill("fengmo-zhang", 1));
                        target->receive_damage("qi", damage, me);

                        result = COMBAT_D->damage_msg(damage, type);
                        result = replace_string( result, "$l", limb);
                        str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));

                        message_vision(result, me, target);
                        message_vision("($N"+str+")\n", target);

                } else {
                        message_vision(YEL "$N看得分明，身形一讓，避過了$n！\n" NOR, target, weapon);
                }
        
                message_vision(HIR "\n$N猛吸一口氣，飄身趕上$n伸掌在杖尾一推，將其又推在半空飛旋。\n\n" NOR, me, weapon);

                addn_temp("fengmo", 1, me);
                call_out("check_fight", 1, me, target, weapon);
        }
}               

int remove_attack(object me, object weapon)
{
        if ( !objectp( me ) ) return 1;
        if( !query_temp("fengmo", me))return 1;
        delete_temp("fengmo", me);
        
        if( file_name(environment(me)) == query_temp("location", me) && living(me)){
                weapon->move(me);
                set("no_clean_up", 0, weapon);
                weapon->wield();
                message_vision(YEL "\n$N縱身上前，將飛旋的$n收回。\n\n" NOR, me, weapon);
        }
        else {
                weapon->move(query_temp("location", me));
                message("vision", "只聽得鏘的一聲，"+weapon->name()+"力盡由半空跌落。\n", environment(weapon), ({weapon}) );
        }
        delete_temp("location", me);

        return 1;
}