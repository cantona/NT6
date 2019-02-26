#include <ansi.h>
#include <combat.h>

#define LUAN "「" HIM "亂劍覆花" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg, wn;
        object weapon;
        int ap, dp;

        me = this_player();

        if( userp(me) && !query("can_perform/furong-jian/luan", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(LUAN "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不對，難以施展" LUAN "。\n");

        if ((int)me->query_skill("furong-jian", 1) < 100)
                return notify_fail("你芙蓉劍法不夠嫻熟，難以施展" LUAN "。\n");

        if (me->query_skill_mapped("sword") != "furong-jian")
                return notify_fail("你沒有激發芙蓉劍法，難以施展" LUAN "。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功火候不夠，難以施展" LUAN "。\n");

        if ((int)me->query_skill("dodge") < 120)
                return notify_fail("你的輕功火候不夠，難以施展" LUAN "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在的真氣不夠，難以施展" LUAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        wn = weapon->name();

        msg = HIM "\n$N" HIM "輕嘯一聲，騰空而起，" + wn + "在空中挽出一個劍"
              HIM "花，頃刻間劍花四散，洋洋灑灑。\n猶如無數花瓣從半空灑向$n"
              HIM "全身。" NOR;

        message_sort(msg, me, target);

        ap = me->query_skill("furong-jian", 1);
        dp = target->query_skill("dodge", 1);

        if (random(ap) >= random(dp / 3))
        {
                 damage = me->query_skill("furong-jian", 1);
                 damage += random(damage / 3);

                 msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           HIR "$n" HIR "只見無數劍花襲來，將自己包圍"
                                           "住，正猶豫間，$n" HIR "已被" + wn + HIR 
                                           "刺得皮開肉綻。\n" NOR);
                 me->start_busy(3);
                 addn("neili", -100, me);
        } else
        {
                 msg = CYN "然而$n" CYN "看出其中的破綻，側身一跳"
                      "已然躲過$N" CYN "這一劍。\n" NOR;

                       me->start_busy(3);
                 addn("neili", -100, me);
        }
        message_combatd(msg, me, target);

        return 1;
}