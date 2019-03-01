#include <ansi.h>
#include <combat.h>

string name() { return HIR "一指點三脈" NOR; }

inherit F_SSERVER;

string *xue_name = ({
"勞宮穴", "膻中穴", "曲池穴", "關元穴", "曲骨穴", "中極穴",
"承漿穴", "天突穴", "百會穴", "幽門穴", "章門穴", "大橫穴",
"紫宮穴", "冷淵穴", "天井穴", "極泉穴", "清靈穴", "至陽穴", });

int perform(object me, object target)
{
        int damage, lvl;
        string msg, wp;
        object weapon;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("jingang-zhi", 1) < 200)
                return notify_fail("你大力金剛指不夠嫻熟，難以施展" + name() + "。\n");

        if ((int)me->query_skill("jingluo-xue", 1) < 200)
                return notify_fail("你對經絡學了解不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("finger") != "jingang-zhi")
                return notify_fail("你沒有激發大力金剛指，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("finger") != "jingang-zhi")
                return notify_fail("你沒有準備大力金剛指，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你的內力修為不足，難以施展" + name() + "。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        damage = damage_power(me, "finger");
        //lvl = (int)me->query_skill("jingang-zhi", 1);
        ap = attack_power(me, "finger");
        dp = defense_power(target, "parry");

        msg = HIW "突然間";

        msg += "$N" HIW "凝氣于指，「" HIR "一指點三脈" HIW "」點出，頓時一股"
               "純陽的內力直襲$n" HIW "胸口！\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 150,
                                           HIR "結果$n" HIR "被$N" HIR "一指點中"
                                           HIY + xue_name[random(sizeof(xue_name))] +
                                           HIR "，全身真氣逆流而上，登時嘔出一大"
                                           "口鮮血。\n" NOR);

                target->start_busy(ap/100 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "鎮定自如，全力化解了$P"
                       CYN "這精妙的一指。\n" NOR;
        }


        me->start_busy(2 + random(3));
        addn("neili", -800, me);
        message_combatd(msg, me, target);

        return 1;
}
