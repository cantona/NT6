// wuqing.c 美女拳-玉女絕情

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "玉女絕情" NOR; }

int perform(object me, object target)
{
        object ob;
        string msg;
        int damage,jiali,married,ap,dp;

        jiali=query("jiali", me);

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("玉女絕情只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須先放下手中的兵器！\n");

        if( query("gender", me) != "女性" )
                return notify_fail("玉女絕情只有女性才能夠使用。\n");

        if( (int)me->query_skill("meinv-quan", 1) < 400 )
                return notify_fail("你的美女拳級別不夠，不會使用玉女絕情。\n");

        if( (int)me->query_skill("force", 1) < 120 )
                return notify_fail("你的內功還未嫻熟，不能用玉女絕情。\n");

        if( query("neili", me)<600 )
                return notify_fail("你現在內力太弱，不能使用玉女絕情。\n");

        if( query("jingli", me)<200 )
                return notify_fail("你現在精力太弱，不能使用玉女絕情。\n");

        msg = HIB "\n\n$N真氣催動，帶得拳意縱橫無情！\n"NOR;
        msg += HIY "\n$N右手支頤，左袖輕輕揮出，長嘆一聲，臉現寂寥之意，無奈中使出殺招。\n\n"NOR;

        ap=attack_power(me, "unarmed");
        dp=defense_power(target, "force");

        if( mapp(query("family", target)) && query("family/family_name", target) == "全真教" )
                ap += ap/3;

        if( ap/2 + random( ap ) > dp || !living(target) )
        {
                damage = damage_power(me, "unarmed");

                //判斷結婚次數和發生性行為的次數
                if( !mapp(query("couple", me)))married=1;
                else married=query("couple/married", me);
                if( mapp(query("sex", me)))married+=query("sex/times", me);
                damage -= (damage/5) * (married - 1);
                if (damage < 10) damage = 10;

                addn("neili", -200, me);
                target->receive_damage("qi", damage,  me);
                target->receive_wound("qi", random(damage*2/3), me);
                target->start_busy(0);

                if ( damage < 1000) {
                        msg += HIR"只聽砰的一聲，$n被一拳擊中小腹，內血翻湧噴口而出。\n"NOR;
                }else if ( damage < 1800) {
                        msg += HIR"只聽砰、砰兩聲，$n左眼發青、右眼發紫，鮮血直流。\n"NOR;
                }else if ( damage < 2600) {
                        msg += HIR"只聽砰、砰、砰三聲響，$n頭部、胸部、腹部同時被重重擊中，鮮血狂噴。\n"NOR;
                }else {
                        msg += HIR"只聽砰、砰、砰、砰巨響絡繹不絕，$n直被打得骨骼碎裂飛了出去。\n"NOR;
                }
                msg += NOR;
                me->start_busy(2+random(2));
        }
        else
        {
                msg += HIG"$n靈光一現，縱身躍起，本能的反應幫$n逃過此劫。\n\n"NOR;
                addn("neili", -100-query("jiali", me), me);
                me->start_busy(2 + random(2));
                message_combatd(msg+"\n", me, target);
                return 1;
        }

        message_combatd(msg+"\n", me, target);
        COMBAT_D->report_status(target);
        return 1;
}
