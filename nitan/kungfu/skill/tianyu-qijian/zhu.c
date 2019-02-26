// This program is a part of NITAN MudLIB
// zhu.c 九羽天誅

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "九羽天誅"; }

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
                return notify_fail("「九羽天誅」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
              || query("skill_type", weapon) != "sword" )
                return notify_fail("你需要一把劍才能施展「九羽天誅」。\n");

        if( query("neili", me)<400 )
                return notify_fail("你的內力所剩無幾，無法施展「九羽天誅」。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力修為不足，無法施展「九羽天誅」。\n");

        if ( me->query_skill("tianyu-qijian", 1) < 100 )
                return notify_fail("你的天羽奇劍不夠嫻熟，不能使用「九羽天誅」。\n");

        if ( me->query_skill("sword", 1) < 100 )
                return notify_fail("你的基本劍法不夠嫻熟，不能使用「九羽天誅」。\n");

        if( query("jiali", me)<1 )
                return notify_fail("你加力太少，無法使用「九羽天誅」。\n");

        if( query("09g/ring", me) == "li" )
        {
                if ( me->query_skill("xiaowuxiang", 1) < 100 )
                        return notify_fail("你的小無相功修為不足，使不出「九羽天誅」絕技。\n");
                if ( me->query_skill_mapped("force") != "xiaowuxiang" )
                        return notify_fail("你沒有使用小無相功，無法使用「九羽天誅」絕技。\n");
        }

        else
        {
                if ( me->query_skill("bahuang-gong", 1) < 100 )
                        return notify_fail("你的八荒六合惟我獨尊功修為不足，使不出「九羽天誅」絕技。\n");
                if ( me->query_skill_mapped("force") != "bahuang-gong" )
                        return notify_fail("你沒有使用八荒六合惟我獨尊功，無法使用「九羽天誅」絕技。\n");
        }

        if( query_temp("09_pfm/zhu", me) )
                return notify_fail("你正在使用「九羽天誅」。\n");

        if( query_temp("09_pfm/yun_duzun", me) )
                return notify_fail("你正在運用「惟我獨尊」心法，無法使用「九羽天誅」！\n");

        if( query_temp("09_pfm/zhu_over", me) )
                return notify_fail("你剛剛使用過「九羽天誅」，此時氣血不調，還是等一下再用吧。\n");

        bonus = me->query_skill("tianyu-qijian", 1) / 30;
        bonus += me->query_skill("sword", 1) /30;
        bonus += me->query_skill("piaomiao", 1) /35;

        addn_temp("apply/attack", bonus, me);
        addn_temp("apply/damage", bonus, me);
        addn_temp("apply/defense", bonus*2, me);

        message_combatd(HIR"\n只聽一聲寶劍破空的龍吟之聲，$N手中的"+weapon->name()+HIR"頓時閃爍出耀眼的光芒，一股股寒氣彌\n"+
                          "漫於周身。忽然$N招式徒然一快，使出一招「"HIW"九羽天誅"HIR"」，霎時間滿天劍影鋪天蓋地，\n"+
                          "彷彿三九天的鵝毛大雪撲面而來，直壓向$n的周身要害，速度更是快得驚人！\n"NOR, me, target);

        hits = bonus/3;

        if ( hits < 3 )
                hits = 3;
        if ( hits > 9 )
                hits = 9;

        set_temp("09_pfm/zhu", hits, me);
        addn("neili", -200, me);

        remove_call_out("check_fight");
        call_out("check_fight", 1, me, target, bonus);

        return 1;
}

void remove_effect(object me, int bonus)
{
        addn_temp("apply/attack", -bonus, me);
        addn_temp("apply/damage", -bonus, me);
        addn_temp("apply/defense", -bonus*2, me);
        delete_temp("09_pfm/zhu", me);
        delete_temp("09_pfm/zhu_hit_done", me);
        set_temp("09_pfm/zhu_over", 1, me);
        if ( me->is_fighting() )
                me->start_busy(3);

        remove_call_out("zhu_done");
        call_out("zhu_done", 12, me);
}

void zhu_done(object me)
{
        if ( !me )
                return;

        tell_object(me, HIY"經過一段時間的休息，你又可以使用「九羽天誅」了！\n"NOR);
        delete_temp("09_pfm/zhu_over", me);
}

void check_fight(object me, object target, int bonus)
{
        if ( !me )
                return;

        if( !me->is_fighting() || !query_temp("09_pfm/zhu", me) || query_temp("09_pfm/zhu", me)<1
             || !target || !living(target) )
        {
                message_combatd(WHT"\n$N長舒了一口氣，手中的劍光也以不似先前一般凌厲了。\n"NOR, me);
                remove_effect(me, bonus);
                return;
        }

        if( query("neili", me)<300 )
        {
                message_combatd(HIR"\n$N額頭冒汗，看來是內力不隨，劍鋒上的光芒一下消失不見了。\n"NOR, me);
                remove_effect(me, bonus);
                return;
        }

        if ( me->query_skill_mapped("sword") != "tianyu-qijian" )
        {
                message_combatd(HIR"\n$N忽然招式一邊，劍上的光芒頓時消失得無影無蹤。\n"NOR, me);
                remove_effect(me, bonus);
                return;
        }

        if( !query_temp("weapon", me) )
        {
                tell_object(me, HIR"\n你的兵器不見了，無法繼續使用「九羽天誅」了。\n"NOR, me);
                remove_effect(me, bonus);
                return;
        }

        remove_call_out("check_fight");
        call_out("check_fight", 1, me, target, bonus);
}

int help(object me)
{
        write(WHT"\n「九羽天誅」\n\n"CYN+
                 " 　　九羽天誅，招如其名，施展開來時猶如滿天鵝毛飄零而下，劍氣縱橫\n"+
                 " 劍影如雪，將敵人前後左右上下圍住，使其避無可避，退無可退。這一招\n"+
                 " 劍法初時只能連發三招，然而當功力有成之時則最多可連出九招，前後一\n"+
                 " 氣呵成，連綿不絕，將敵人壓在一層層巨浪之下，實是厲害不過。\n\n"+

                 " "HIR"注"WHT"：此招不可與「惟我獨尊」心法同時使用。\n\n"+

              WHT" 要求：八荒六合唯我獨尊功　"HIR"100"WHT" 級\n"+
              WHT" 　　　小無相功          　"HIR"100"WHT" 級\n"+
              WHT" 　　　天羽奇劍  　　　　　"HIR"100"WHT" 級\n"+
              WHT" 　　　基本劍法　　　　　　"HIR"100"WHT" 級\n"+
              WHT" 　　　當前內力  　　　　 "HIR" 400"WHT" 點\n"+
              WHT" 　　　最大內力　　　　　 "HIR"1000"WHT" 點\n\n"+

              WHT" 戰鬥中使用。\n"NOR);

        return 1;
}