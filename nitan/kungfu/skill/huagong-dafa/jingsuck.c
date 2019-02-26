// Code of ShenZhou
// jingsuck.c

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int exert(object me, object target)
{
        int sp, dp, jing, jing1, eff_jing;

        if( !target ) target = offensive_target(me);

        if( !objectp(target) || target == me)
                return notify_fail("你要吸取誰的精神？\n");

        if( query("no_fight", environment(me)) )
                return notify_fail("這裏不能戰鬥，你不可以使用化功大法吸人的精神。\n");

        if( query_temp("sucked", me) )
                return notify_fail("你剛剛吸取過精神！\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你的化功大法功力不夠，必須空手才能施用化功大法吸人精神！\n");

        if( !me->is_fighting() || !target->is_fighting() || !living(target) )
                return notify_fail("你必須在戰鬥中才能吸取對方的精神！\n");

        if( (int)me->query_skill("huagong-dafa",1) < 45 )
                return notify_fail("你的化功大法功力不夠，不能吸取對方的精神。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的內力不夠，不能使用化功大法。\n");

        if( query("jingli", me)<20 )
                return notify_fail("你的精力不夠，不能使用化功大法。\n");

        if( query("jing", target)<query("max_jing", target)/5
          || query("jingli", target)<query("max_jingli", target)/10 )
                return notify_fail( target->name() +
                        "已經精神渙散，你已經無法從他體內吸取精力了！\n");

        message_vision(
                HIR "$N突然神祕的一笑，雙掌一前一後對準$n的太陽穴拍了過來！\n\n" NOR,
                me, target );

        if( !target->is_killing(me) ) target->kill_ob(me);

        sp=me->query_skill("force")+me->query_skill("dodge")+query("kar", me)*50;
        dp=target->query_skill("force")+target->query_skill("dodge")+query("kar", target)*50;
        sp+=query("combat_exp", me)/1000;
        dp+=query("combat_exp", target)/1000;

        set_temp("sucked", 1, me);

        if( random(sp+dp) > dp )
        {
                tell_object(target, HIR "你猛覺額角兩側如針刺般劇痛，神志迷困，頭腦中一片空白！\n" NOR);
                tell_object(me, HIG "你覺得" + target->name() + "的精力自手掌源源不絕地流了進來。\n" NOR);

                target->receive_damage("jing", (int)me->query_skill("huagong-dafa", 1)/5 );

                if( query("eff_jing", me)<query("max_jing", me) )
                        me->receive_curing("jing", (int)me->query_skill("huagong-dafa", 1)/10);
                else addn("jing", me->query_skill("huagong-dafa",1)/5, me);

                if( query("combat_exp", target) >= query("combat_exp", me)/2){
                        addn("potential", 1, me);
                        addn("combat_exp", 1, me);
                        if( query("potential", me)>me->query_potential_limit() )
                        set("potential", me->query_potential_limit(), me);
                }

                me->start_busy(random(3));
                target->start_busy(random(3));
                addn("neili", -me->query_skill("huagong-dafa",1)/6, me);
                addn("jingli", -5, me);

                call_out("del_sucked", 2, me);
        }
        else
        {
                addn("neili", -20, me);
                message_vision(HIY "可是$p看破了$P的企圖，機靈地閃了開去。\n" NOR, me, target);
                me->start_busy(3);
                call_out("del_sucked", 4, me);
        }

        return 1;
}

void del_sucked(object me)
{
        if( query_temp("sucked", me) )
        delete_temp("sucked", me);
}
