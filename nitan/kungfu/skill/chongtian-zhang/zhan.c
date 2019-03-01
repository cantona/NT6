#include <ansi.h>
#include <combat.h>

#define ZHAN "「" HIW "翅展九州" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if( userp(me) && !query("can_perform/chongtian-zhang/zhan", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHAN "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(ZHAN "只能空手施展。\n");

        if (me->query_skill("force") < 150)
                return notify_fail("你的內功火候不夠，難以施展" ZHAN "。\n");

        if ((int)me->query_skill("chongtian-zhang", 1) < 120)
                return notify_fail("你的白鶴沖天掌不夠嫻熟，難以施展" ZHAN "。\n");

        if (me->query_skill_mapped("strike") != "chongtian-zhang")
                return notify_fail("你沒有激發白鶴沖天掌，難以施展" ZHAN "。\n");

        if (me->query_skill_prepared("strike") != "chongtian-zhang")
                return notify_fail("你沒有準備白鶴沖天掌，難以施展" ZHAN "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真氣不夠，難以施展" ZHAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N" HIW "雙臂舒張，掌緣微微顫動，身形一展，已移至$n"
              HIW "跟前，雙掌交叉奮力劈下，正是\n白鶴沖天掌「翅展九州」"
              "絕技，空氣中頓時爆響出一陣尖銳的破空聲。\n" NOR;

        addn("neili", -50, me);
        ap = me->query_skill("strike");
        dp = target->query_skill("force");
        if (ap / 2 + random(ap) > dp)
        {
                damage = me->query_skill("strike") * 3 / 5;
                damage += random(damage / 3);
                addn("neili", -100, me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30,
                                           HIR "$n" HIR "躲閃不得，只能硬擋下雙掌"
                                           "，頓時被$P" HIR "雙掌砍中雙肩兩側，吐"
                                           "血不止！\n" NOR);
                me->start_busy(3);
        } else
        {
                msg += CYN "可是$p" CYN "奮力招架，終于將$P"
                       CYN "這雙掌架開，沒有受到任何傷害。\n"NOR;
                me->start_busy(4);
        }
        message_combatd(msg, me, target);

        return 1;
}