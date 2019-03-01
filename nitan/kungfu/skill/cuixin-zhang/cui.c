#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "奪命催心"; }

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp;
        int damage, lvl;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("奪命催心只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) )
                return notify_fail("你必須是空手才能使用奪命催心！\n");

        lvl = me->query_skill("cuixin-zhang", 1);

        if (lvl < 120)
                return notify_fail("你的催心掌還不夠純熟！\n");

        if (me->query_skill("force") < 120)
                return notify_fail("你的內功火候太低，無法使出奪命催心。\n");

        if( query("neili", me)<800 )
                return notify_fail("你的內力不夠，無法使出奪命催心。\n");

        msg = HIR "$N" HIR "聚氣于掌，仰天一聲狂嘯，剎那間雙掌交錯，一招"
                  "「奪命催心」帶著陰毒內勁直貫$n" HIR "！\n"NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "parry");


        if ( ap / 2 + random(ap) > dp )
        {
                addn("neili", -300, me);
                damage = damage_power(me, "strike");
                target->affect_by("cuixin_zhang",
                        (["level":query("jiali", me)+random(query("jiali", me)),
                             "id":query("id", me),
                      "duration" : lvl / 50 + random(lvl / 20) ]));

                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 50,
                        HIR "只聽$n" HIR "慘叫一聲，只感兩耳轟"
                        "鳴，目不視物，噴出一大口鮮血，軟軟癱倒。\n" NOR);

                me->start_busy(2);
        } else
        {
                msg += HIY "$p見$P來勢洶湧，急忙縱身一躍而起，躲開了這致命的一擊！\n" NOR;
                addn("neili", -300, me);
                me->start_busy(3);
        }

        message_combatd(msg, me, target);

        return 1;
}