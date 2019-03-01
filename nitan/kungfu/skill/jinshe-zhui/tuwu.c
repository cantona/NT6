// This program is a part of NITAN MudLIB
// tuwu.c

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, ap, dp;
        int damage;
        string msg;
        object weapon;

        /*
        if( query_temp("jinshe/tuwu", me) )
                return notify_fail("你才用的金蛇吐霧，沒法接著就出招。\n");
        */

        if (! target) target = offensive_target(me);
        if (! target || ! me->is_fighting(target))
                return notify_fail("金蛇吐霧只能在戰鬥中使用。\n");

        if( !objectp(weapon=query_temp("handing", me)) || 
            // (string)weapon->query("id") != "jinshe zhui" ||
            weapon->query_amount() < 1)
                // return notify_fail("你手裡沒拿金蛇錐，不能使用絕招！\n");
                return notify_fail("你手裡沒拿金蛇錐或其他暗器，不能使用絕招！\n");

        if ((skill = me->query_skill("jinshe-zhui", 1)) < 100)
                return notify_fail("你的金蛇錐法不夠嫻熟，不會使用金蛇吐霧。\n");

        if( query("neili", me)<300 )
                return notify_fail("你內力不夠了。\n");

        if( query_temp("jinshe/tuwu", target) )
                return notify_fail("對方已經這樣了，你就不必了吧。\n");

        weapon->add_amount(-1);

        msg = HIY "$N" HIY "一聲輕嘯，身形微動，手中金蛇錐竟然向上飛"
              "起繞了個圈，隨而迅速襲向$n" HIY "的面前。\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");
             
        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -200, me);
                damage = damage_power(me, "strike");
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage / 3, me);
        
                msg += HIM "只聽一陣狂風掃葉般的聲響中，$N" HIM "手中的"
                       "金蛇錐閃出奪目的光芒，閃耀得$n" HIM "眼冒金花，"
                       "\n除了眼前一重重的霧氣外，$n" HIM
                       "啥也看不見了！\n" NOR;
                message_combatd(msg, me, target);
                set_temp("jinshe/tuwu", 1, target);
                set_temp("block_msg/all", 1, target);
                me->start_call_out((: call_other, __FILE__, "tuwu_end", me, target :),
                                   skill / 100);
        } else
        {
                msg += CYN "$n" CYN "心中暗暗一驚，急忙後"
                       "退，閃開了這枚金蛇錐。\n" NOR;
                message_combatd(msg, me, target);
        }

        me->reset_action();
        return 1;
}

void tuwu_end(object me, object target)
{
        if (target && living(target))
        {
                message_combatd("$N抹了抹滿臉的" HIR "鮮血" NOR "，終于睜開了眼。\n",
                                target);
                set_temp("block_msg/all", 0, target);
                write(HIR "你終于抹掉了滿臉的鮮血，看到了周圍的情景。\n"NOR);
                delete_temp("jinshe/tuwu", target);
        }

        return;
}