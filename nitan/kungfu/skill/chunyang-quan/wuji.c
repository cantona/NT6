// Code of Shenzhou
// creat by Karlopex@sz
/*************************************************************************************
perform wuji （「純陽無極」）--中高手在出神通之前一個重要進攻性pfm，快速攻擊一招，威力巨大，但所費內力同樣巨大。
條件：純陽拳等級200，先天功等級200。（注：不是有效等級）
功能：增加20% attack
限制：只可與pfm sanhua 或者 perform yanwu之一組合使用。
      威力巨大，busy時間稍長 20 tick +或至戰鬥結束。
      所費內力與威力成正比。威力越大，內力需求越多。skill*2
描述：$1運起先天功之純陽內勁，太陽穴高高鼓起，面如金箔，所發拳招竟帶出嗤嗤聲響，從不可思議方位向$1擊來一招。
***************************************************************************************/               
#include <ansi.h>
#include <combat.h>

inherit F_DBASE;
inherit F_SSERVER;

void chkpfm(object me, object target, int amount);

int perform(object me, object target)
{
        int skill, damage, time, jiali, jiajin;
        string weapon;
        string *limb, type, result, str;

        if( !target ) target = offensive_target(me);

        if( !target
        ||        !target->is_character()
        ||        !me->is_fighting(target)
        ||      !living(target) )
                return notify_fail("「純陽無極」只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("「純陽無極」需空手才能施展！\n");

        if( me->query_skill_mapped("cuff") != "chunyang-quan" )
                return notify_fail("你所用的並非純陽拳，不能施展「純陽無極」！\n");

        if( me->query_skill_prepared("cuff") != "chunyang-quan" )
                return notify_fail("你所備的並非純陽拳，不能施展「純陽無極」！\n");

        if( me->query_skill_mapped("force") != "xiantian-gong" )
                return notify_fail("你所用的並非玄門先天功，施展不出「純陽無極」！\n");

        if( me->query_skill("xiantian-gong",1) < 199 )
                return notify_fail("你的玄門先天功火候未到，無法施展「純陽無極」！\n");

        if( me->query_skill("chunyang-quan", 1) < 199 )
                return notify_fail("「純陽無極」需要精湛的純陽拳方能有效施展！\n");

        skill = me->query_skill("force") + me->query_skill("cuff");
        jiali=query("jiali", me);
        jiajin=query("jiajin", me);
        if( query("neili", me) <= skill*3/2 )
                return notify_fail("你的內力不夠使用「純陽無極」！\n");
        if( query("jingli", me) <= skill )
                return notify_fail("你的精力不夠使用「純陽無極」！\n");

        addn_temp("apply/attack", skill/3, me);
        addn_temp("apply/damage", skill/6, me);
        message_vision(HIG "\n\n$N運起先天功之純陽內勁，太陽穴高高鼓起，面如金箔，所發拳招竟帶出嗤嗤聲響，從不可思議的方位向$n攻出一招！！！\n" NOR, me, target);
        chkpfm(me, target, skill);
        addn_temp("apply/attack", -skill/3, me);
        addn_temp("apply/damage", -skill/6, me);
        if (skill > 800) skill = 800;
        if( query_temp("cyq-wuji", me) == "ok3"){
                addn("neili", -(skill+jiali)*4/5, me);
                addn("jingli", -(skill+jiajin)*2/3, me);
        }else if( query_temp("cyq-wuji", me) == "ok2"){
                addn("neili", -(skill+jiali)/4, me);
                addn("jingli", -(skill+jiajin)/5, me);
        }else if( query_temp("cyq-wuji", me) == "ok1"){
                addn("neili", -(skill+jiali)/2, me);
                addn("jingli", -(skill+jiajin)/3, me);
        }else{
                addn("neili", -(skill+jiali)/8, me);
                addn("jingli", -(skill+jiajin)/10, me);
        }
        delete_temp("cyq-wuji", me);
        me->start_busy( 1+random(2) );
        return 1;
}

void chkpfm(object me, object target, int amount)
{
        object weapon2=query_temp("weapon", target);
        string *limbs, action, limb, attack_skill, dodge_skill, parry_skill, result, msg = "", *type = ({"擦傷","瘀傷","內傷"});
        int ap, dp, pp, damage, level, sp, sp2, ap2, jiali, jiajin;
        if( !me->is_fighting(target) || !living(target) ) 
                return;
        jiali=query("jiali", me);
        jiajin=query("jiajin", me);
        attack_skill = me->query_skill_mapped("cuff");
        action = me->query_action()["action"];

        damage = (amount * me->query_skill("cuff") / 200)+(jiali+jiajin)*me->query_skill("xiantian-gong", 1)/200;
        if (damage > 10000)damage = 10000;
        ap = atoi(COMBAT_D->skill_power(me, SKILL_USAGE_ATTACK));
        if( ap < 1) ap = 1;
        ap2 = atoi(COMBAT_D->skill_power(me, "cuff", SKILL_USAGE_ATTACK));
        dp = atoi(COMBAT_D->skill_power(target, "dodge", SKILL_USAGE_DEFENSE));
        sp = atoi(COMBAT_D->skill_power(me, "dodge", SKILL_USAGE_DEFENSE));
        limbs=query("limbs", target);
        limb = limbs[random(sizeof(limbs))];
        if( target->is_busy() ) dp /= 4;
        if( dp < 1 ) dp = 1;
        if( random(ap + dp) < random(dp) )
        {
                if (wizardp(me)) tell_object(me,"ap:"+ap+"   dp:"+dp+".\n");
                dodge_skill = target->query_skill_mapped("dodge");
                if ( !dodge_skill ) dodge_skill = "dodge";
                if ( random( dp  * 9 / 10 ) < random(sp) ){
                        msg += HIY "\n$n以"+to_chinese(dodge_skill)+"的身法閃過這一擊，身形尚未停穩，被$N搶先欺身到前。\n" NOR;
                        msg += HIG "\n" + action + "！\n" +NOR;
                        target->receive_damage("qi", damage/3, me);
                        target->receive_wound("qi", damage/5, me);
                        result = COMBAT_D->damage_msg(damage, type[random(sizeof(type))]);
                        msg += replace_string( HIR+result+NOR, "$l", limb );
                        set_temp("cyq-wuji", "ok1", me);
                }else msg += SKILL_D(dodge_skill)->query_dodge_msg();
        }
        else
        {
                pp = atoi(COMBAT_D->skill_power(target, "parry", SKILL_USAGE_DEFENSE));
                if( target->is_busy() ) pp /= 3;
                if( pp < 1 ) pp = 1;

                if( random(ap + pp) < random(pp))
                {
                        if (wizardp(me)) tell_object(me,"ap:"+ap+"   pp:"+pp+".\n");
                        parry_skill = target->query_skill_mapped("parry");
                        if( !parry_skill || !SKILL_D(parry_skill)->parry_available()) 
                                parry_skill = "parry";
                        if ( random(ap2) > random(pp * 3 / 2) && !weapon2 ){
                                msg += HIY "\n$n以"+to_chinese(parry_skill)+"的招式生生接下這一擊，結果$N的招式殺傷巨大。\n" NOR;
                                target->receive_damage("qi", damage/6, me);
                                target->receive_wound("qi", damage/10, me);
                                result = COMBAT_D->damage_msg(damage, type[random(sizeof(type))]);
                                msg += replace_string( HIR+result+NOR, "$l", limb );
                                set_temp("cyq-wuji", "ok2", me);
                        }else msg += SKILL_D(parry_skill)->query_parry_msg(weapon2, target);
                }
                else 
                {
                        target->receive_damage("qi", damage, me);
                        target->receive_wound("qi", damage/2, me);
                        result = COMBAT_D->damage_msg(damage, type[random(sizeof(type))]);
                        msg += replace_string( HIR+result+NOR, "$l", limb );
                        set_temp("cyq-wuji", "ok3", me);
                }
        }
        message_vision(replace_string( msg, "$l", limb )+"\n", me, target);
        if (wizardp(me)) tell_object(me, HIY"damage =====> "+damage+".\n"NOR);
        return;
}
