// This program is a part of NT MudLIB
// qiong.c 瓊樓玉宇

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "瓊樓玉宇"; }

int perform(object me, object target)
{
        int bonus, hits;
        object weapon;


        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「瓊樓玉宇」只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) )
                return notify_fail("空手才能施展「瓊樓玉宇」。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        if( query("neili", me)<400 )
                return notify_fail("你的內力所剩無幾，無法施展「瓊樓玉宇」。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力修為不足，無法施展「瓊樓玉宇」。\n");

        if ( me->query_skill("mingyu-gong", 1) < 200 )
                return notify_fail("你的明玉神功不夠嫻熟，不能使用「瓊樓玉宇」。\n");

        if ( me->query_skill("unarmed", 1) < 200 )
                return notify_fail("你的基本拳腳不夠嫻熟，不能使用「瓊樓玉宇」。\n");

        if( query("jiali", me)<1 )
                return notify_fail("你加力太少，無法使用「九羽天誅」。\n");

        if ( me->query_skill_mapped("force") != "mingyu-gong" )
                return notify_fail("你的內功沒有使用明玉功，無法使用「瓊樓玉宇」絕技。\n");
        if ( me->query_skill_mapped("parry") != "mingyu-gong" )
                return notify_fail("你的招架沒有使用明玉功，無法使用「瓊樓玉宇」絕技。\n");
        if ( me->query_skill_mapped("unarmed") != "mingyu-gong" )
                return notify_fail("你的拳腳沒有使用明玉功，無法使用「瓊樓玉宇」絕技。\n");
        if ( me->query_skill_mapped("dodge") != "mingyu-gong" )
                return notify_fail("你的輕功沒有使用明玉功，無法使用「瓊樓玉宇」絕技。\n");
        if( query("gender", me) != "女性" )
                return notify_fail("你並非純陰之體，無法使用「瓊樓玉宇」絕技。\n");
        if( query_temp("mingyu_pfm/qiong", me) )
                return notify_fail("你正在使用「瓊樓玉宇」。\n");

        if( query_temp("mingyu_pfm/qiong_over", me) )
                return notify_fail("你剛剛使用過「瓊樓玉宇」，此時氣血不調，還是等一下再用吧。\n");

        bonus = me->query_skill("mingyu-gong", 1) / 3;
        bonus += me->query_skill("unarmed", 1) /3;
        bonus += me->query_skill("force", 1) /3;

        addn_temp("apply/attack", bonus, me);
        addn_temp("apply/unarmed_damage", bonus, me);
        addn_temp("apply/defense", bonus*2, me);

         message_combatd(WHT"〖"HIY"瓊樓玉宇"WHT"〗\n\n"HIG"只見$N分光勁勢再抖，像蛟龍出海，大鵬展翅，
先是一團光芒，光芒驀然爆開，化作一片光雨，漫天遍地向$n刺來！\n" NOR, me, target);

        set_temp("mingyu_pfm/qiong", bonus, me);
        addn("neili", -200, me);

        // call_out("check_fight", 1, me, target, bonus);
         me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me, bonus :), bonus/4);

        return 1;
}

void remove_effect(object me, int bonus)
{
        addn_temp("apply/attack", -bonus, me);
        addn_temp("apply/unarmed_damage", -bonus, me);
        addn_temp("apply/defense", -bonus*2, me);
        delete_temp("mingyu_pfm/qiong", me);
        set_temp("mingyu_pfm/qiong_over", 1, me);
        if ( me->is_fighting() && !me->is_busy() )
                me->start_busy(3);

        me->start_call_out((: call_other, __FILE__, "qiong_done", me : ), 3);
}

void qiong_done(object me)
{
        if ( !me )
                return;

        tell_object(me, HIY"經過一段時間的休息，你又可以使用「瓊樓玉宇」了！\n"NOR);

        delete_temp("mingyu_pfm/qiong_over", me);
}

void check_fight(object me, object target, int bonus)
{
        if ( !me )
                return;

        if( !me->is_fighting() || !query_temp("mingyu_pfm/qiong", me) || query_temp("mingyu_pfm/qiong", me)<1
             || !target || ! (living(target)) )
        {
                message_combatd(WHT"\n$N長舒了一口氣，手中的無形勁氣也以不似先前一般凌厲了。\n"NOR, me);
                remove_effect(me, bonus);
                return;
        }

        if( query("neili", me)<300 )
        {
                message_combatd(HIR"\n$N額頭冒汗，看來是內力不隨，手上的勁道一下消失不見了。\n"NOR, me);
                remove_effect(me, bonus);
                return;
        }

        if ( me->query_skill_mapped("unarmed") != "mingyu-gong" )
        {
                message_combatd(HIR"\n$N忽然招式一邊，手上的勁道頓時消失得無影無蹤。\n"NOR, me);
                remove_effect(me, bonus);
                return;
        }

        if( query_temp("weapon", me) )
        {
                tell_object(me, HIR"\n你裝備上兵器，無法繼續使用「瓊樓玉宇」了。\n"NOR, me);
                remove_effect(me, bonus);
                return;
        }

        remove_call_out("check_fight");
        call_out("check_fight", 1, me, target, bonus);
}


