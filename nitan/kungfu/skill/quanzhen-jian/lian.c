
//再拆數招，尹志平左劍平刺，右掌正擊，同時左腿橫掃而出，
//正是全真派中的“三連環”絕招。

#include <ansi.h>

inherit F_SSERVER;

string name() { return "三連環"; }

int perform(object me, object target)
{
        int addon, ap, dp, damage, count, limit, limit2;
        string str;
        object weapon, weapon1;

        weapon=query_temp("weapon", me);
        weapon1=query_temp("secondary_weapon", me);

        if( !weapon || query("skill_type", weapon) != "sword" )
                return notify_fail("你手中無劍，如何使用全真劍法的三連環絕技？\n");

        if(!target ) target = offensive_target(me);

        if(!target || !target->is_character() || !me->is_fighting(target))
                return notify_fail("「三連環」只能對戰鬥中的對手使用。\n");

        if (me->query_skill("sword",1)<150)
                return notify_fail("你的基本功還不夠紮實。\n");

        if (me->query_skill("quanzhen-jian",1)<180)
                return notify_fail("你的全真劍法修為不夠。\n");

        if( me->query_skill_mapped("sword") != "quanzhen-jian" )
                return notify_fail("你所用的並非全真劍法。\n");

        if( query("neili", me) <= 350 )
                return notify_fail("你的內力不夠使用「三連環」！\n");

        if( query("jingli", me) <= 250 )
                return notify_fail("你的精力不夠使用「三連環」！\n");

        if( me->query_skill_mapped("strike") != "haotian-zhang" &&
            me->query_skill_mapped("strike") != "chongyang-shenzhang")
                return notify_fail("你所用的並非全真的掌法，不能施展「三連環」！\n");

         if( me->query_skill_prepared("strike") != "haotian-zhang" &&
             me->query_skill_prepared("strike") != "chongyang-shenzhang")
                return notify_fail("你所備的並非全真的掌法，不能施展「三連環」！\n");

        addn_temp("quanzhen/lh_count", 1, me);

        if( query_temp("quanzhen/lh_count", me)>30 )
                set_temp("quanzhen/lh_count", 1, me);

        addn("neili", -350, me);
        addn("jingli", -250, me);
        me->start_busy(3);

        count=query_temp("quanzhen/lh_count", me);
        limit=180;
        if (count<=10) tell_object(me, HIG"\n\n你精神抖擻，內力充沛，出招格外凌厲。\n\n"NOR);
        if (count>10 && count<=20) {
                tell_object(me, HIG"\n\n你反復使用□三連環□，招數已經沒有以前凌厲，但仍然咄咄逼人。\n\n"NOR);
                limit=120;
        }
        if (count>20) {
                tell_object(me, HIG"\n\n你使用太多次□三連環□，精力渙散，招數已經失去了原有的凌厲。\n\n"NOR);
                limit=60;
        }

        addon = me->query_skill("sword")/4;
        if (addon > limit) addon = limit;

        addn_temp("apply/attack", addon, me);
        addn_temp("apply/damage", addon/2, me);

        message_vision(HIR"拆得數招，$N左劍平刺，右掌正擊，同時左腿橫掃而出，正是全真派中的“三連環”絕招。\n"NOR,me,target);

        COMBAT_D->do_attack(me, target, weapon, 1);

        weapon->unequip();
        if (objectp(weapon1))     weapon1->unequip();

        COMBAT_D->do_attack(me, target, 0, 1);

        weapon->wield();
        if (objectp(weapon1))     weapon1->wield();

        ap=query("combat_exp")/1000+me->query_skill("sword", me)+me->query_skill("unarmed",1);
        dp=query("combat_exp")/1000+target->query_skill("parry", target);

        if(me->query_skill("unarmed",1)>50) message_vision(HIY,me,target);
        message_vision("\n$N身法一變，唰地一腿，貼地向$n橫掃而出，只帶得地上塵土飛揚。\n"NOR,me,target);

        if(random(ap)>dp/2 || !living(target))
        {
                damage=me->query_skill("quanzhen-jian",1)*(random(6)+3);

                message_vision(HIR"\n只見$n躲閃不及，已經被$N一腿掃中，慘叫聲中，向後跌出丈許。\n"NOR, me, target);

                if (damage<500) damage=500;

                if (limit==100) damage=200;

                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", random(damage), me);

                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                message_vision("($N"+str+")\n", target);

                target->start_busy(3);
        } else {
                message_vision(HIY"\n$n見此招來勢兇猛，向後一躍，輕巧地躲了開去。\n"NOR,me,target);
                if(limit==100)
                {
                        message_vision(HIR"\n$N用力過猛，收勢不住，“哎喲”一聲，摔了一交。\n"NOR,me,target);
                        addn("eff_qi", -random(400), me);
                        str=COMBAT_D->status_msg(query("qi", me)*100/query("max_qi", me));
                        message_vision("($N"+str+")\n", me);
                }
                me->start_busy(2);
        }

        addn_temp("apply/attack", -addon, me);
        addn_temp("apply/damage", -addon/2, me);
        return 1;
}
