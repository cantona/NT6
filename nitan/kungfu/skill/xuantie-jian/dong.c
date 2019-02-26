#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "大江東去" NOR; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        int ap, dp;
        string wp, msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        wp = weapon->name();

        if ((int)me->query_skill("xuantie-jian", 1) < 200)
                return notify_fail("你的玄鐵劍法不夠嫻熟，難以施展" + name() + "。\n");

        /*
        if ((int)weapon->query_weight() < 25000)
                return notify_fail("你手中的" + wp + "分量不夠，難以施展" + name() + "。\n");
        */

        if( query("neili", me)<800 )
                return notify_fail("你現在的內力不足，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "xuantie-jian")
                return notify_fail("你沒有激發玄鐵劍法，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "$N" HIW "暗自凝神，頓時一股氣勁由身後澎湃迸發，接着單"
              "手一振，手中" + wp + HIW "\n隨即橫空卷出，激得周圍塵沙騰起"
              "，所施正是玄鐵劍法「" HIG "大江東去" HIW "」。\n"NOR;

        me->start_busy(2);

        ap = attack_power(me, "sword") + me->query_str()*10;
        dp = defense_power(target, "force") + target->query_str()*10;

        if( query("character", me) == "光明磊落" || query("character", me) == "國土無雙" )
                ap += ap / 5;

        if (ap / 2 + random(ap) > dp)
        {
                if (! target->is_busy())
                        target->start_busy(1);
                damage = damage_power(me, "sword");
                damage+= query("jiali", me);
                addn("neili", -600, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90,
                                           HIR "結果$n" HIR "奮力招架，卻被$N" HIR
                                           "這一劍震的飛起，口中鮮血狂吐不止！\n" NOR);
        } else
        {
                msg += CYN "可是$n" CYN "看破了$N"
                       CYN "的企圖，急忙斜躍避開。\n"NOR;
                addn("neili", -300, me);
        }
        message_combatd(msg, me, target);

        return 1;
}