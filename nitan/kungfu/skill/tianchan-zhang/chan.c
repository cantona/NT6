#include <ansi.h>
#include <combat.h>

string name() { return HIR "毒蟾掌" NOR; }

inherit F_SSERVER;

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
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) )
                return notify_fail("你必須是空手才能使用" + name() + "。\n");

        if (me->query_skill_mapped("strike") != "tianchan-zhang")
                return notify_fail("你沒有激發天蟾掌法，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "tianchan-zhang")
                return notify_fail("你沒有準備使用天蟾掌法，難以施展" + name() + "。\n");

        lvl = me->query_skill("tianchan-zhang", 1);

        if (lvl < 120)
                return notify_fail("你天蟾掌法不夠純熟，難以施展" + name() + "。\n");

        if (me->query_skill("force") < 150)
                return notify_fail("你的內功火候太低，，難以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的內力不夠，，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIR "$N" HIR "一聲冷笑，聚氣于掌，飛身一躍而起，一招"
                  "攜滿劇毒的「毒蟾掌」對著$n" HIR "凌空拍下！\n"NOR;

        ap = attack_power(me, "strike") + lvl;
        dp = defense_power(target, "parry");

        if ( ap / 2 + random(ap) > dp )
        {
                addn("neili", -200, me);
                damage = damage_power(me, "strike");
                target->affect_by("tianchan_zhang", ([
                        "level":query("jiali", me)+random(query("jiali", me)),
                        "id":query("id", me),
                        "duration" : lvl / 60 + random(lvl / 30)
                ]));
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 70,
                        HIR "只聽$n" HIR "慘叫一聲，被$N" HIR "這一掌"
                        "拍個正著，頓時毒氣攻心，“哇”地噴出一大口鮮血。\n" NOR);

                me->start_busy(2);
        } else
        {
                msg += HIY "$p" HIY "見$P" HIY "來勢洶湧，急忙縱身一躍而起，躲"
                       "開了這一擊！\n" NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}