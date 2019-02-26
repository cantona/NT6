// /kungfu/skill/dragon-strike/xianglong.c  perform 降龍一擊
// Rama 2001/11/11

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "降龍一擊"; }

void remove_effect(object me, object target, int lvl);
void msg_display(object me, object target, int lvl);

int perform(object me, object target)
{
        object armor;
        int lvl;
        /*
        mixed my_exp;

        my_exp=query("combat_exp", me);
        */

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("你不在戰鬥中。\n");

        if( query_temp("yield", me) )
                return notify_fail("你不出掌，如何使出降龍一擊？\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你不是空手。\n");

        if( query_temp("xianglong", me)){
                return notify_fail("你已在使用降龍一擊！\n");
        }

        if( query("max_jingli", me)<500 )
                return notify_fail("你的精力修為不夠，無力施展降龍一擊！\n");

        if( query("max_neili", me)<6000 )
                return notify_fail("你的內力修為不夠，無力施展降龍一擊！\n");

        if( me->query_skill("force") < 550 )
                return notify_fail("你的混天氣功火候未到，無法施展降龍一擊！\n");

        if( (lvl = me->query_skill("strike")) < 550 )
                return notify_fail("你的降龍十八掌修為不夠！\n");

        if ( me->query_skill_mapped("force") != "huntian-qigong")
                                         return notify_fail("你所用內功不對！\n");

        if( query("neili", me) <= lvl*2 )
                                         return notify_fail("你的內力不夠！\n");

        if( query("jingli", me) <= 500 )
                                         return notify_fail("你的精力不夠！\n");

        set_temp("xianglong", 1, me);
        message_combatd(HIR "$N氣聚丹田，雙掌自外向裏轉了個圓圈，緩緩的凝聚全身功力。\n\n" NOR, me,target);
        addn("neili", -lvl/2, me);
        addn("jingli", -lvl/5, me);
        lvl = (int)(lvl / 5);

        addn_temp("apply/defense", lvl, me);
        me->start_busy(1+random(2));

        call_out("msg_display",1+(int)((me->query_skill("strike")-300)/50),me,target,lvl);

        return 1;
}

void msg_display(object me, object target, int lvl)
{
        string *circle, msg;

        if (!me) return;

        if (!target ||
            !target->is_character() ||
            !me->is_fighting(target) ||
            !living(me))
        {
                delete_temp("xianglong", me);
                addn_temp("apply/defense", -lvl, me);
                return;
        }


        circle = ({
                "$N突然大喝一聲，雙掌齊出，向$p當胸猛擊過去。\n",
                "$N大步邁出，左手一劃，右手呼的一掌，猛向$p擊去。\n"
        });

        msg = HIG"\n"+ circle[random(sizeof(circle))] +"\n" NOR;

        circle = ({
                "掌力未到，$p已感胸口呼吸不暢，頃刻之間，$N的掌力如怒潮般洶湧而至。",
                "只一瞬之間，$p便覺氣息窒滯，$N掌力竟如怒潮狂湧，勢不可當，又如是一堵無形的高牆，向$p身前疾衝。"
        });

        msg += HIG"\n"+ circle[random(sizeof(circle))] +"\n" NOR;

        if( target
            &&  target->is_character()
            &&  me->is_fighting(target) ) {
                message_combatd(msg, me, target);
                call_out("remove_effect",2,me,target,lvl);
        } else {
                delete_temp("xianglong", me);
                addn_temp("apply/defense", -lvl, me);
        }
        return 0;
}

void remove_effect(object me, object target, int lvl)
{
        int jiali, jianu, ap, dp, pp,dmg,damage;
        object weapon;
        string *limbs, limb, result, str, type;

        if (!me) return;

        if (!target ||
            !target->is_character() ||
            !me->is_fighting(target) ||
            !living(me))
        {
                delete_temp("xianglong", me);
                addn_temp("apply/defense", -lvl, me);
                return;
        }

        weapon=query_temp("weapon", target);
        jiali=query("jiali", me);
        jianu=query("jianu", me)*5;
        ap = me->query_skill("strike");
        ap += (jiali + jianu)/4;
        ap *= 2;
        if (living(target))
        {
            pp = target->query_skill("parry");
            dp = target->query_skill("dodge");
        }  else
        {
            pp = 0;
            dp = 0;
        }
        type = "內傷";

        if( target
        &&      target->is_character()
        &&      me->is_fighting(target) ) {

        if (wizardp(me))
                printf("ap=%d,pp=%d,dp=%d,query_temp(apply/defense, me)=%d,lvl=%d.\n",ap,pp,dp,query_temp("apply/defense", me),lvl);

        if( ap/2 + random(ap) > dp + pp ) {
            message_combatd(HIM"$N的雙掌已跟着擊到，砰的一聲呼，重重打中$p胸口，跟着喀喇喇幾聲，肋骨斷了幾根。\n"NOR, me, target);
            dmg = ap;
            dmg += jiali + jianu*5;
            dmg += random(dmg/2);

        if (wizardp(me))
                printf("damage = %d\n",dmg);

            target->receive_damage("qi", dmg,  me);
            target->receive_wound("qi", dmg/2+random(dmg/2), me);
            target->start_busy(1+random(2));

            addn("neili", -dmg/3, me);
            addn("jingli", -dmg/6, me);

            limbs=query("limbs", target);

            result = COMBAT_D->damage_msg(dmg, type);
            result = replace_string( result, "$l", limbs[random(sizeof(limbs))]);
            result = replace_string( result, "$p", target->name() );
            message_combatd(result, me, target);

            str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
            message_combatd("($N"+str+")\n", target);
        } else {
            if ( objectp(weapon) )
            {
                message_combatd(HIC "$n大驚之下，$p連劃三個半圓護住身前，同時足尖着力，飄身後退，避開了$N的一掌。\n" NOR, me, target, weapon);
            }
            else {
                message_combatd(HIC "$n大驚之下，雙掌連劃三個半圓護住身前，同時足尖着力，飄身後退，避開了$N的一掌。\n" NOR, me, target);
            }
        }
        }
        me->start_busy(2+random(2));
        delete_temp("xianglong", me);
        addn_temp("apply/defense", -lvl, me);
        return 0;
}
