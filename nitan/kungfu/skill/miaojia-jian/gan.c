// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { HIY "流星趕月" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int ap, dp, wn;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if ((int)me->query_skill("miaojia-jian", 1) < 200)
                return notify_fail("你苗家劍法不夠嫻熟，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 280 )
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的內力修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<600 )
                return notify_fail("你現在真氣不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "miaojia-jian")
                return notify_fail("你沒有激發苗家劍法，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        wn = weapon->name();

        msg = HIY "$N" HIY "凝聚內力，手中" + wn + HIY "迸出萬道光華，驀然間破空"
              "聲驟響，" + wn + HIY "竟離手射出，流星般向$n" HIY "奔去！\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "sword");

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 65,
                                           HIR "$n" HIR "頓時大驚失色，只覺胸口處"
                                           "一涼，那柄" + wn + HIR "竟然已經穿胸透"
                                           "過，帶出一蓬血雨！\n" NOR);
                addn("neili", -500, me);
        } else
        {
                me->start_busy(3);
                msg += HIC "$n" HIC "見" + wn + HIC "來勢洶湧，心知絕"
                       "不可擋，當即向後橫移數尺，終于躲閃開來。\n" NOR;
                addn("neili", -500, me);
        }

        if (userp(me) && (int)me->query_skill("miaojia-jian", 1) < 260)
        {
                msg += HIY "只見" + wn + HIY "余勢不盡，又向前飛出數"
                       "丈，方才沒入土中。\n" NOR;
                weapon->move(environment(me));
        } else
                msg += HIY "然而$N" HIY "身形一展，登時躍出數丈，掌"
                       "出如風，將射出的" + wn + HIY "又抄回手中。\n" NOR;

        message_combatd(msg, me, target);
        return 1;
}