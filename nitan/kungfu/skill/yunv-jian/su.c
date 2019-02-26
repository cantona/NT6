// This program is a part of NT MudLIB
// suxing.c 素心訣

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "素心決"; }

void remove_effect(object me, int skill);

int perform(object me, object target)
{
        string msg;
        object weapon;
        int damage,ap,dp,married;

        if( query("gender", me) != "女性" )
                return notify_fail("玉女素心只能是女的用！\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("素心訣只能對戰鬥中的對手使用。\n");

        if( me->query_skill_mapped("force") != "yunv-xinfa" )
                return notify_fail("你所用的並非玉女心法，無法施展素心訣！\n");

        if( me->query_skill("yunv-xinfa", 1) < 200 )
                return notify_fail("你的玉女心法火候未到，無法施展素心訣！\n");

        if( me->query_skill("yunv-jian", 1) < 200 )
                return notify_fail("你的玉女素心劍法火候未到，無法施展素心訣！\n");

        if( !(weapon=query_temp("weapon", me)) || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的兵器不對。\n");

        if( !stringp(me->query_skill_mapped("sword")) ||
            me->query_skill_mapped("sword") != "yunv-jian")
                return notify_fail("你必須激發玉女素心劍作為劍法才能夠使用素心訣。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你的內力不夠使用玉女素心！\n");

        if( query("jingli", me)<500 )
                return notify_fail("你的精力不夠使用玉女素心！\n");

        message_combatd(HIW "$N突然面色莊重，雙目清澄，手中" +
                       query("name", weapon)+HIW+"蒙上了一層白霜，寒氣逼人！\n\n"NOR,me);
        message_combatd(HIW "$N騰身而起，姿態無比婀娜飄逸，揮劍向$n直刺過去，快愈流星！\n\n"NOR,me,target);

        ap = attack_power(me, "sword") + me->query_skill("force");
        dp = defense_power(target, "parry") + me->query_skill("force");

        if( mapp(query("family", target)) && query("family/family_name", target) == "全真教" )
                ap += ap/3;

        if( query("can_learn/yunv-xinfa/wall", me) )
                ap *= 2;

        if (ap/2 + random(ap) > dp || !living(target))
        {
                damage = damage_power(me, "sword");
                if( query("can_learn/yunv-xinfa/wall", me) ) damage *= 2;
                //判斷結婚次數和發生性行為的次數
                if( !mapp(query("couple", me)))married=1;
                else married=query("couple/married", me);
                if( mapp(query("sex", me)))married+=query("sex/times", me);
                damage -= (damage/5) * (married - 1);
                if (damage < 10) damage = 10;
/*
                target->receive_damage("qi", damage/2 + random(damage/2), me);
                target->receive_wound("qi", damage, me);
*/
                msg=HIR"只聽$n一聲慘呼，已然給$N的"+NOR+query("name", weapon)+HIR+
                      "重重的刺中，渾身上下凝結上一層白色冰霜，冷的瑟瑟發抖！\n"NOR;
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 200, msg);
                if (!target->is_busy())
                        target->start_busy(1+random(2));
                me->start_busy(2);
        } else
        {
                msg = HIY "$n見狀大驚失色，雙足點地，抽身急退，堪堪避過$N的這記素心訣，已是大汗淋漓。\n"NOR;
                me->start_busy(2+random(4));
        }
        message_combatd(msg, me, target);
        return 1;
}
