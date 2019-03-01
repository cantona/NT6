#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIM "千姿百媚" NOR; }

int perform(object me, object target)
{
        string msg, wn;
        object weapon;
        int ap, dp;

        me = this_player();

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不對，難以施展" + name() + "。\n");

        if ((int)me->query_skill("yunv-jian", 1) < 40)
                return notify_fail("你玉女劍法不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "yunv-jian")
                return notify_fail("你沒有激發玉女劍法，難以施展" + name() + "。\n");

        if ((int)me->query_skill("dodge") < 60)
                return notify_fail("你的輕功修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<60 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        wn = weapon->name();

        msg = HIC "\n$N" HIC "陡然間姿態萬千，身法飄逸，猶如一個婀娜"
              "多姿的女子在隨歌漫舞一樣。\n但是$N手中" + wn + HIC "卻"
              "跟隨著身體輕盈地晃動，看似毫無章法，卻又像是隱藏著厲"
              "害的招式。" NOR;

        message_combatd(msg, me, target);

        addn("neili", -50, me);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg = HIY "$N" HIY "看不出$n" HIY "招式中的虛實，連忙"
                      "護住自己全身，一時竟無以應對！\n" NOR;
                target->start_busy(2 + random(ap / 100));
        } else
        {
                msg = CYN "可是$N" CYN "看出了$n" CYN "這招乃虛招，頓"
                      "時一絲不亂，鎮定自若。\n" NOR;

                me->start_busy(2);
        }
        message_combatd(msg, target, me);

        return 1;
}