#include <ansi.h>
#include <combat.h>

#define DIAN "「" HIR "魁星點元" NOR "」"

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        int ap, dp, damage;
        string wn, msg;

        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/baxian-jian/dian", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(DIAN "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" DIAN "。\n");

        if (me->query_skill("force") < 150)
                return notify_fail("你的內功的修為不夠，難以施展" DIAN "。\n");

        if (me->query_skill("baxian-jian", 1) < 100)
                return notify_fail("你的八仙劍法修為不夠，難以施展" DIAN "。\n");

        if (me->query_skill_mapped("sword") != "baxian-jian")
                return notify_fail("你沒有激發八仙劍法，難以施展" DIAN "。\n");

        if( query("neili", me)<250 )
                return notify_fail("你現在真氣不夠，難以施展" DIAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        wn = weapon->name();

        msg = HIC "$N" HIC "施出「" HIR "魁星點元" HIC "」絕技，手中" + wn +
              HIC "微作龍吟，劍尖迸出一道劍氣射向$n" HIC "。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           (: final, me, target, damage :));
                me->start_busy(2);
                addn("neili", -150, me);
        } else
        {
                msg += CYN "可是$p" CYN "並不慌亂，收斂心神，輕輕格擋開了$P"
                       CYN "的劍招。\n"NOR;
                me->start_busy(3);
                addn("neili", -60, me);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        addn("neili", -damage, target);

        if( query("neili", target)<0 )
                set("neili", 0, target);

        return  HIR "結果$n" HIR "不慎被$N" HIR "劍尖盪出的"
                "劍氣點中勞宮穴，全身真氣不禁狂泄而出！\n" NOR;
}