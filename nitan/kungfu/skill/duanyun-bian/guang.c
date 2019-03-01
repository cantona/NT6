// wuguang.c 斷雲鞭法「日月無光」

#include <ansi.h>

inherit F_SSERVER;

string name() { return "日月無光"; }
int perform(object me, object target)
{
        int damage, power;
        string msg;
        object weapon;
        int ap, dp;

        if( !objectp(target) ) {target = offensive_target(me);}

        if( !target || !target->is_character() || target == me ||
                  !me->is_fighting(target) ||
          !living(target) || query_temp("noliving", target) )
                return notify_fail(name()+"只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "whip" )
                return notify_fail(HIR"裝備鞭才能使用「日月無光」？\n"NOR);

        if( me->query_skill("duanyun-bian", 1) < 150 )
                return notify_fail("你的斷雲鞭法火候不夠，使不出"+name()+"。\n");

        if( me->query_skill("whip",1) < 150 )
                return notify_fail("你的鞭法的基本功不紮實！\n");

        if( query("max_neili", me)<600 )
                return notify_fail(RED"你內力修為不足，無法運足內力。\n"NOR);

        if( query("neili", me)<600 )
                return notify_fail(HIC"你現在內力不夠，沒能將"+name()+"使完！\n"NOR);

        msg=HIC"$N"HIC"一聲大喝，右手一振，手中"+query("name", weapon)+HIC"脫手飛出。只見滿天鞭影，盤旋繚繞，遮閉天日，劈頭蓋腦向$n"HIC"砸了下去！\n"NOR;
        ap = attack_power(me, "whip");
        dp = defense_power(target, "force");
        if( ap / 2 + random(ap) > dp )
        {
                if( query("shen", me)>1000000 )
                        power = 1000000;
                else if( query("shen", me)>0 )
                        power=query("shen", me);
                else power = 3000;
                if( query("shen", target)<0 )
                        power=power*2;
                damage = damage_power(me, "whip") + random((int)(power/1000))+(int)(power/3000);
                addn("neili", -600, me);
                me->start_busy(2);
                if( !target->is_busy() )
                        target->start_busy(random(3));
                target->receive_damage("qi", damage,me);
                target->receive_wound("qi", damage/2,me);
                target->receive_damage("jing", damage/4,me);
                msg += HIR"$n疾忙返身後躍，但鞭勢疾如電閃，但見黑影如壓城之勢而來，全身如遭"
                       "雷擊，一時不知挨了多少鞭，不禁慘聲連連！\n"NOR;
        } else
        {
                me->start_busy(2);
                msg += HIY"可是$n"HIY"一縱數丈，一下就躍出了$N的鞭影。\n"NOR;
                addn("neili", -200, me);
        }
        msg+=HIC+query("name", weapon)+HIC+"落下，倒插在地上，猶振然弄威作響。\n"NOR;
        weapon->move(environment(me));
        message_combatd(msg, me, target);

        return 1;
}
