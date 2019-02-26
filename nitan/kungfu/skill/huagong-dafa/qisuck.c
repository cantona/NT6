// Code of ShenZhou
// qisuck.c

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int exert(object me, object target)
{
        int sp, dp;
        int dmg;

        if( !target ) target = offensive_target(me);

        if( !objectp(target) || target == me)
                return notify_fail("你要吸取誰的真氣？\n");

        if( query("no_fight", environment(me)) )
                return notify_fail("這裏不能戰鬥，你不可以使用化功大法吸人的精力。\n");

        if( query_temp("sucked", me) )
                return notify_fail("你剛剛吸取過真氣！\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("必須空手才能夠吸取別人的精力！\n");

        if( !me->is_fighting() || !target->is_fighting() || !living(target) )
                return notify_fail("你必須在戰鬥中才能吸取對方的真氣！\n");

        if( (int)me->query_skill("huagong-dafa",1) < 50 )
                return notify_fail("你的化功大法功力不夠，不能吸取對方的真氣。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠，不能使用化功大法。\n");

       if( query("jingli", me)<30 )
                return notify_fail("你的精力不夠，不能使用化功大法。\n");

        if( query("qi", target)<query("max_qi", target)/5 )
                return notify_fail( target->name() +
                        "已經真氣渙散，你已經無法從他體內吸取真氣了！\n");

        message_vision(
                HIB "$N突然詭異的一笑，雙手一揚，拇指對準$n的掌心按了過來！\n\n" NOR,
                me, target );

        if( !target->is_killing(me) ) target->kill_ob(me);

        sp=me->query_skill("force")+me->query_skill("dodge")+query("kar", me)*50;
        dp=target->query_skill("force")+target->query_skill("dodge")+query("kar", target)*50;
        sp+=query("combat_exp", me)/1000;
        dp+=query("combat_exp", target)/1000;

        set_temp("sucked", 1, me);

        if( random(sp+dp) > dp )
        {
                tell_object(target, HIR "你突然覺得全身真氣自手掌奔湧而出，四肢無力，再也使不出勁來！\n" NOR);
                tell_object(me, HIG "你覺得" + target->name() + "的真氣自手掌源源不絕地流了進來。\n" NOR);
                message_vision(
                        HIR "$N覺得全身真氣自手掌奔湧而出，四肢無力，再也使不出勁來！\n\n" NOR,
                        target );

                addn("qi", me->query_skill("force"), me);

                if( query("combat_exp", target) >= query("combat_exp", me)/2 )
                        addn("combat_exp", 1, me);

                me->start_busy(random(2));
                target->start_busy(random(2));
                addn("neili", -me->query_skill("force")/6, me);
                addn("jingli", -5, me);

                dmg=random(me->query_skill("force")/100)*query("neili", me)/10;
                if( dmg > 2000) dmg=2000;
                if( dmg <100) dmg=100;
                dmg = random(dmg);
                target->receive_damage("qi", dmg, me );
                target->receive_wound("qi", random(dmg), me);

                COMBAT_D->report_status(target);

                call_out("del_sucked", 1, me);
        }
        else
        {
                message_vision(HIY "可是$p看破了$P的企圖，機靈地閃了開去。\n" NOR, me, target);
                addn("jingli", -10, me);
                me->start_busy(2);
                call_out("del_sucked", 2+random(2), me);
        }

        return 1;
}

void del_sucked(object me)
{
        if( query_temp("sucked", me) )
        delete_temp("sucked", me);
}
