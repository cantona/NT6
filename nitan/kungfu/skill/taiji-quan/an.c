// an.c 太極拳「按」字訣

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "按字訣"; }

int perform(object me, object target)
{
        int damage, acter, ap, dp, taoism;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「按字訣」只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能使用「按字訣」！\n");

        if ((int)me->query_skill("taiji-quan", 1) < 200)
                return notify_fail("你對太極拳理的理解還不夠，不會使用「按字訣」。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在真氣太弱，不能使用「按字訣」。\n");

        msg = HIG "$N" HIG "雙拳上下揮動，使出太極拳「按字訣」，$n"
              HIG "感到一股強大的勁力從頭頂壓落。\n" NOR;

        addn("neili", -200, me);

        dp = (defense_power(target, "parry") + target->query_skill("force", 1)) / 3;

        if( query("character", me) == "光明磊落" ||
            query("character", me) == "國土無雙" ||
            query("character", me) == "狡黠多變" )
               acter = 3;
        else
               acter = 4;

        taoism = me->query_skill("taoism", 1);

        ap = (attack_power(me, "cuff") + me->query_skill("taiji-shengong", 1) +
              taoism) / acter;

        if (target->is_bad())   ap += ap / 2;

        if (random(ap) > dp / 2 || !living(target))
        {
                me->start_busy(2);
                if( !target->is_busy() )
                        target->start_busy(1+random(3));

                damage = damage_power(me, "cuff");

                if( query("shen", me)/800<5000 )
                     damage += 5000;
                else
                     damage+=query("shen", me)/800;

                damage+=query("jiali", me)*2;

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK,
                                           damage, 70,
                                           HIY "$n" HIY "登感呼吸不暢，胸悶難當，"
                                           HIY "喉頭一甜，狂噴數口"HIR"鮮血"HIY"！\n"
                                           ":內傷@?");
        } else
        {
                me->start_busy(3);
                msg += HIY "$p" HIY "急運內功，聚勁於外，挺身硬接了$P"
                       HIY "這一招，“砰”的一聲巨響，雙方各自震退數步！\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}
