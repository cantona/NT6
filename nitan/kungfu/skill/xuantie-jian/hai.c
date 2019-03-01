// This program is a part of NITAN MudLIB
// 海潮洶湧

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "海潮洶湧"; }

string *xue_name = ({
        "勞宮穴","膻中穴","曲池穴","關元穴","曲骨穴","中極穴","承漿穴","天突穴","百會穴",
        "幽門穴","章門穴","大橫穴","紫宮穴","冷淵穴","天井穴","極泉穴","清靈穴","至陽穴",
});

int perform(object me, object target)
{
        string msg, dodge_skill;
        int i, j, ap, dp;
        object weapon;

        if( query("gender", me) == "男性" )
        {
                i = me->query_skill("xuantie-jian", 1) / 4;
                j = me->query_skill("sword", 1) / 4;
        }
        else
        {
                i = me->query_skill("xuantie-jian", 1) / 5;
                j = me->query_skill("sword", 1) / 5;
        }
        weapon=query_temp("weapon", me);

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("玄鐵劍法的「海潮洶湧」只能在戰鬥中對對手使用。\n");

        if( !weapon || query("skill_type", weapon) != "sword" )
                return notify_fail("你必須使用武器才能使用「海潮洶湧」！\n");

        if ((int)me->query_skill("xuantie-jian", 1) < 130)
                return notify_fail("你的玄鐵劍法還不夠嫻熟，使不出「海潮洶湧」絕技。\n");

        if ((int)me->query_skill("surge-force", 1) < 130
        &&  (int)me->query_skill("surge-force", 1) < 130)
                return notify_fail("你的古墓內功等級還不夠，使不出「海潮洶湧」絕技。\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("你的內功等級不夠，不能使用「海潮洶湧」。\n");

        if ((int)me->query_str() < 33)
                return notify_fail("你的膂力還不夠強勁，使不出「海潮洶湧」來。\n");

        if( query_temp("xtjf/haichao", target) || target->is_busy() )
                return notify_fail(target->name()+"正自顧不暇，你可以放心地進攻。\n");

        if (me->query_skill_mapped("sword") != "xuantie-jian" && userp(me))
                return notify_fail("你現在無法使用「海潮洶湧」！\n");

        if (me->query_skill_mapped("parry") != "xuantie-jian" && userp(me))
                return notify_fail("你現在無法使用「海潮洶湧」！\n");

        if( query("max_neili", me)<(me->query_skill("force")+j+200) )
                return notify_fail("你現在內力太弱，使不出「海潮洶湧」。\n");

        message_combatd(HIB"\n$N持"+query("name", weapon)+
                        HIB "挾巨浪潮湧之勢，劍氣形成一個旋轉的氣渦，向$n籠罩過去。\n" NOR,
                        me, target);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                message_combatd(HIR "結果$n全身被劍氣所形成的氣渦所籠罩著，只覺得猶如身陷洪濤巨浪，跌跌撞撞。\n" NOR,
                                me, target);

                if( !target->is_busy() )
                        target->start_busy(2 + ap / 80);
                set_temp("xtjf/haichao", 1, target);
                addn("neili", -i*3, me);
                COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);

                if (me->query_skill("xuantie-jian", 1) > 180)
                {
                        remove_call_out("remove_effect");
                        call_out("remove_effect", 1, me, target);
                }

                if ((int)me->query_skill("xuantie-jian", 1) > 150
                 && query("neili", me)>(me->query_skill("force",1)+j )
                &&  present(target, environment(me))
                &&  me->is_fighting(target))
                {
                        message_combatd(HIB"\n$N微笑不語，趁勢將手中的"+query("name", weapon)+
                                        HIB "從輕而響，從響而輕，忽寂然無聲，忽轟轟之聲，向$n席卷而去。\n" NOR,
                                        me, target);

                        if (random(me->query_skill("sword", 1)) > target->query_skill("parry", 1) / 3
                        ||  ! living(target)
                         || query("level", me)>query("level", target) )
                        {
                                addn_temp("apply/str", i, me);
                                addn_temp("apply/attack", j, me);
                                addn_temp("apply/damage", j, me);
                                set_temp("xtjf_pfm", 1, me);
                                COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);
                                COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);
                                addn_temp("apply/str", -i, me);
                                addn_temp("apply/attack", -j, me);
                                addn_temp("apply/damage", -j, me);

                                addn("neili", -200, me);
                                delete_temp("xtjf_pfm", me);
                        } else
                        {
                                addn("neili", -100, me);
                                dodge_skill = target->query_skill_mapped("dodge");
                                if (! dodge_skill ) dodge_skill = "dodge";
                                        msg = SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
                                message_combatd(msg, me, target);
                        }
                        return 1;
                }
        } else
        {
                me->start_busy(2+random(2));
                addn("neili", -100, me);
                dodge_skill = target->query_skill_mapped("dodge");
                if (! dodge_skill ) dodge_skill = "dodge";
                        msg = SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
                message_combatd(msg, me, target);
        }
        return 1;
}

void remove_effect(object me, object target)
{
        remove_call_out("remove_effect");
        if (! me) return;
        if (objectp(target) && ! me->is_fighting(target))
        {
                delete_temp("xtjf", target);
                return;
        }
        if (objectp(target)
        &&  me->is_fighting(target)
        &&  ! target->is_busy()
        &&  random(2) == 1
         && query_temp("weapon", me) )
        {
                delete_temp("xtjf", target);
                call_out("perform2", 1, me, target);
                return;
        }
        call_out("remove_effect", 1 ,me ,target);
}

int perform2(object me, object target)
{
        string msg, dodge_skill,name;
        object weapon=query_temp("weapon", me);
        int p, ap, dp, damage;

        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return 0;

        if( !weapon || query("skill_type", weapon) != "sword" )
                return 0;
        if( me->query_skill_mapped("sword") != "xuantie-jian" && userp(me))
                return 0;

        if( me->query_skill_mapped("parry") != "xuantie-jian" && userp(me))
                return 0;

        if( query("neili", me)<1000 )
                return 0;

        if( query("gender", me) == "女性" )
                p = me->query_skill("force", 1) / 6;
        else
                p = me->query_skill("force", 1) / 8;

        name = xue_name[random(sizeof(xue_name))];
        msg =HIB"\n$n好不容易緩過勁來，$N身形飄忽，轉了幾轉，移步向西，緊跟一劍刺向$n的"RED+name+HIB"。\n"NOR;

        ap=attack_power(me, "sword");
        dp=defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                msg += CYN"$n頓覺眼前一陣迷惑，一時不備，身上的"RED+name+CYN"已被"+weapon->name()+CYN"點中。\n"NOR;
                addn_temp("apply/attack", -p/2, target);
                addn_temp("apply/defense", -p/2, target);
                target->set_temp("xtjf/haichao");
                target->receive_damage("qi", damage,  me);
                target->receive_wound("qi", random(damage/2)+damage/2, me);
                if( random(2) == 1)
                {
                        target->apply_condition("no_perform", 1+ random(2));
                        target->set_temp("xtjf/perform");
                }
                else
                {
                        target->apply_condition("no_exert", 1+random(2));
                        target->set_temp("xtjf/exert");
                }
                addn("neili", -p*6, me);
                call_out("check_fight", 1, me, target, weapon, p );
        }
        else {
                me->start_busy(2+random(2));
                addn("neili", -100, me);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                        msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
        }
        message_combatd(msg, me, target);
        return 1;
}

void check_fight(object me,object target,object weapon, int p)
{
        remove_call_out("check_fight");
        if( !target) return;
        if( ! me
         || ! me->is_fighting("target")
          || !query_temp("weapon", me )
          || query("skill_type", weapon) != "sword"
         || ! present(target,environment(me))
         || me->query_skill_mapped("sword") != "xuantie-jian"){
                addn_temp("apply/attack", p/2, target);
                addn_temp("apply/defense", p/2, target);
                if( query_temp("xtjf/perform", target) )
                        target->clear_condition("no_perform");
                if( query_temp("xtjf/exert", target) )
                        target->clear_condition("no_exert");
                delete_temp("xtjf", target);
                message_combatd(HIW"\n$N竭力掙脫了糾纏，身形恢復了原先的矯捷。\n"NOR, target);
                return ;
        }
        call_out("check_fight", 1, me, target, weapon, p );
}
