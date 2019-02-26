// This program is a part of NT MudLIB

#include <ansi.h>

inherit F_SSERVER;

string name() { return "發射暗器"; }

void remove_shoot(object);

int perform(object me, object target)
{
        int t=query_temp("baituo/shoot", me);
        string type, *limbs, str, dodge_skill, limb, result;
        object weapon;
        int poi_amount, level, exp1, exp2;

        if( query("no_fight", environment(me)) )
                return notify_fail("這裏不能發射暗器。\n");

        if( !target && me->is_fighting()) target = offensive_target(me);

        if (!target || !target->is_character())
                return notify_fail("你要對誰發射暗器？\n");

        if( target == me )
                return notify_fail("對自己發射暗器？\n");

        if( t && (time()-t) < 10 )
                return notify_fail("你剛剛才發射了暗器，短時間內不宜故技重施！\n");

        if( !objectp(weapon=query_temp("weapon", me)) )
                 return notify_fail("你必需手持能發射暗器的蛇杖。\n");

        type=query("snake_type", weapon);

        if( !type && query("id", weapon) != "shezhang" )
                return notify_fail("你的"+weapon->name()+"上並沒有暗器機關。\n");

        level = (int)me->query_skill("lingshe-zhangfa", 1);
        if (level < 40 )
                return notify_fail("你的靈蛇杖法不夠嫻熟，無法操縱發射暗器的機關。\n");

        if ((int)me->query_skill("poison", 1) < 40 )
                return notify_fail("你的基本毒技造詣太淺，無法操縱發射暗器的機關。\n");

        if(( me->query_skill_mapped("force") != "hama-gong") && ( me->query_skill_mapped("force") != "jiuyin-hamagong"))
                return notify_fail("你所用的內功與「靈蛇杖法」氣路相悖！\n");

        limbs=query("limbs", target);
        //level = level/2;
        poi_amount = level + me->query_skill("poison", 1);

        if( query("neili", me)<poi_amount )
                return notify_fail("你的內力不夠。\n");
        if( query("jingli", me)<50 )
                return notify_fail("你的精力不夠。\n");

        exp1=query("combat_exp", me);
        exp2=query("combat_exp", target);

        if(exp1*3<exp2 && exp2> 1000000)
                return notify_fail("你料知"+target->name()+"這等身手，杖頭暗器也奈何他不得，不如不發，免惹恥笑。\n");

        message_combatd(HIB"$N將"+weapon->name()+HIB"在地下一頓，嗚的一聲怪響，杖頭中飛出一件奇形暗器，筆直往$n射去。\n"NOR, me, target);

        addn("neili", -poi_amount/2, me);
        addn("jingli", -50, me);

        if( query("neili", me)>random(query("neili", target)) && (exp1/100)>random(exp2/100)){

                message_combatd(HIR"那暗器去得好快，祗聽$n一聲慘嚎，尚未看清暗器來路，已被射中"+(arrayp(limbs)?limbs[random(sizeof(limbs))]:"身體")+"！\n"NOR, me, target);

                if( type == "怪蛇" || type == "靈蛇" )
                     target->apply_condition("snake_poison",
                        poi_amount*3 + target->query_condition("snake_poison"));
                else
                     target->apply_condition("snake_poison",
                        poi_amount*3 + target->query_condition("snake_poison"));
                set("poisoner", me, target);
                target->receive_wound("qi", random(level) + level/2 , me);
                target->start_busy(random(2));
                result=COMBAT_D->eff_status_msg(query("qi", target)*100/query("max_qi", target));
                message_combatd("( $N"+result+" )\n", target);

        }
        else {
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                str = SKILL_D(dodge_skill)->query_dodge_msg(limb);
                message_vision(str, me, target);
        }

        target->kill_ob(me);
        set_temp("baituo/shoot", time(), me);
        call_out("remove_shoot", 5, me);
        me->start_busy(random(2));

        return 1;
}

void remove_shoot(object me)
{
        if( !me || !query_temp("baituo/shoot", me))return ;

        delete_temp("baituo/shoot", me);
        tell_object(me, "你的蛇杖裏的暗器準備好了。\n");
}
