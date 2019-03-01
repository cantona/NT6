// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "魔氣血殺"; }

int perform(object me, object target)
{
        string msg;
        int ski_value, max_lv;
        int ap, dp, damage;
        int f = 0;

        ski_value = random(me->query_skill("mingyu-gong", 1));
        max_lv = me->query_skill("mingyu-gong", 1);

        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("『魔氣血殺』只能對戰鬥中的對手使用。\n");

        if( me->query_skill("mingyu-gong", 1) < 500 )
                return notify_fail("你的明玉功功力不足。 \n");

        if( me->query_skill("force", 1) < 500 )
                return notify_fail("你的內功不夠好。 \n");

        if( query("neili", me)<1000 )
                return notify_fail("你的內力不夠。\n");

        if (me->query_skill_mapped("force") != "mingyu-gong")
                return notify_fail("你現在沒有激發明玉功為內功，難以施展『魔氣血殺』。\n");

        msg = HIY "$N自殘己身，以血氣轉換成殺氣。\n
            ……$N身上發出一股強大的殺氣……\n
    ■$N身上殺氣逐漸地聚集在雙手,在雙手上形成兩團魔氣■\n
            $N倏地大喝一聲－－魔 氣 血 殺－－\n\n" NOR;

        ap = attack_power(me, "force");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR BLINK "$N突然喉頭一動～～　只見$N口中噴出一道血柱往$n射去～～\n
此乃魔氣殺之
            最終殺招 『魔 血 氣 殺』\n\n
$n遭到前所未有的打擊,但$N也受傷不輕。\n" NOR;

                damage = damage_power(me, "force");
                damage+= query("jiali", me);
                damage*=2;

                if (! target->is_busy())
                        target->start_busy( 3 + random(2) );
                target->receive_wound("jing", damage/2, me);
                //target->receive_wound("qi", damage, me);

                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 200, msg);
                me->receive_wound("qi",query("qi", me)*1/10);
                addn("neili", -500, me);

                f = 1;
        }
        else if( random(4) > 2 )
        {
                msg += HIR BLINK"$N真氣所轉換的殺氣不夠大,對敵人毫無影響。\n" NOR;
                me->receive_wound("qi",query("qi", me)*1/100);
                addn("neili", -200, me);
        }
        else
        {
                msg += HIR BLINK"$n受到強大的殺氣傷害，動彈不得。\n" NOR;
                me->receive_wound("qi",query("qi", me)*5/100);
                target->receive_damage("qi", (int)me->query_skill("mingyu-gong", 1), me);
                if (! target->is_busy())
                        target->start_busy(3);
                addn("neili", -300, me);
        }

        message_combatd(msg, me, target);
        if( f )
                COMBAT_D->report_status(target);
        me->start_busy(3 + random(2));
        return 1;
}

