#include <ansi.h>
#include <combat.h>

string name() { return HIW "風雨交加" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, count;
        int i, attack_time;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "blade" )
                return notify_fail("你所使用的武器不對，難以施展" + name() + "。\n");

        if ((int)me->query_skill("longcheng-shendao", 1) < 120)
                return notify_fail("你的龍城神刀不夠嫻熟，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force", 1) < 150)
                return notify_fail("你的內功修為不足，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "longcheng-shendao")
                return notify_fail("你沒有激發龍城神刀，難以施展" + name() + "。\n");

        if( query("neili", me)<270 )
                return notify_fail("你目前的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIC "$N" HIC "大喝一聲，施出絕招「" HIW "風雨交加" HIC "」手"
              "中的" + weapon->name() + HIC "如雨點\n一般向$n" HIC "打去，$n" HIC
              "如同小舟一般在刀雨中漂泊不定。\n" NOR;

        attack_time = 3;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "dodge");

        attack_time += random(ap / 40);

        if (attack_time > 7)
                attack_time = 7;

        addn("neili", -attack_time*25, me);

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIY "這陣刀勢變化莫測，$n" HIY "頓時覺得眼花繚亂，無法抵擋。\n" NOR;
                count = ap / 35;
                addn_temp("apply/attack", count, me);
        } else
        {
                msg += HIC "$n" HIC "不禁心中凜然，不敢有半點小覷，使出渾身解數抵擋。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me, target, weapon, 20);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(3));

        return 1;
}
