#include <ansi.h>
#include <combat.h>

#define ZHUI "「" HIM "毒龍雙錐" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage;
        object ob;

        if( userp(me) && !query("can_perform/tianlong-jian/zhui", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHUI "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" ZHUI "。\n");

        if ((int)me->query_skill("tianlong-jian", 1) < 120)
                return notify_fail("你的天龍劍法火候太淺，難以施展" ZHUI "。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功修為太淺，難以施展" ZHUI "。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的內力修為太淺，難以施展" ZHUI "。\n");

        if (me->query_skill_mapped("sword") != "tianlong-jian")
                return notify_fail("你沒有激發天龍劍法，難以施展" ZHUI "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在的真氣不足，，難以施展" ZHUI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        ap = me->query_skill("sword");
        dp = target->query_skill("parry");

        damage = ap / 3 + random(ap / 2);

        msg = HIM "$N" HIM "一聲清嘯，手中" + weapon->name() + HIM "急速旋轉，劍尖"
              "作錐，劍身頓時騰起一股旋風，向$n" HIM "鑽去。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 30,
                                           HIR "$n" HIR "招架不住，哧地一聲，$N"
                                           HIR "手中的" + weapon->name() + HIR
                                           "頓時破體鑽入，鮮血四濺！\n" NOR);
        } else
        {
                msg += CYN "可是$n" CYN "奮力格擋，終于架開了$N"
                       CYN "的這一劍。\n" NOR;
        }

        msg += HIM "\n$N" HIM "隨即抽劍回轉，撩下劈上，手中" + weapon->name() + HIM 
               "劍尖一顫，又激盪出一股旋渦勁鑽向$n" HIM "。\n" NOR;
        if (ap * 2 / 5 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           HIR "$n" HIR "急忙抽身後退，可只見$N"
                                           HIR + weapon->name() + HIR "劍芒一漾"
                                           "，胸口便噴出一股血柱！\n" NOR);
        } else
        {
                msg += CYN "可是$n" CYN "凝神聚氣，飛身一躍而起，避開了$N"
                       CYN "的殺著。\n" NOR;
        }
        me->start_busy(2 + random(3));
        addn("neili", -350, me);
        message_combatd(msg, me, target);
        return 1;
}
