// This program is a part of NT MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "陽關三疊" NOR; }
string *xue_name = ({
"勞宮穴", "膻中穴", "曲池穴", "關元穴", "曲骨穴", "中極穴",
"承漿穴", "天突穴", "百會穴", "幽門穴", "章門穴", "大橫穴",
"紫宮穴", "冷淵穴", "天井穴", "極泉穴", "清靈穴", "至陽穴", });

int perform(object me, object target)
{
        int damage;
        string msg, wp;
        object weapon;
        int ap, dp;
        int n;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("sun-finger", 1) < 200)
                return notify_fail("你一陽指訣不夠嫻熟，難以施展" + name() + "。\n");

        if ((int)me->query_skill("jingluo-xue", 1) < 200)
                return notify_fail("你對經絡學了解不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("finger") != "sun-finger")
                return notify_fail("你沒有激發一陽指訣，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("finger") != "sun-finger")
                return notify_fail("你沒有準備一陽指訣，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你的內力修為不足，難以施展" + name() + "。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        damage = damage_power(me, "finger");
        if( (n = me->query_skill("qimai-liuzhuan", 1) / 100) >= 1 )
                damage += damage * n * 15/100;
        ap = attack_power(me, "finger");
        dp = defense_power(target, "parry");

        if( n > 1 ) msg = HIW "$N" HIW "默運氣脈流轉，突然間"; else
        msg = HIW "突然間";

        if( objectp(weapon=query_temp("weapon", target)) )
        {
                wp = weapon->name();
                msg += "$N" HIW "單指一揚，徑點$n" HIW "持著" + wp + NOR + HIW
                       "的手腕上「" HIY "腕骨" HIW "」、「" HIY "陽谷" HIW "」"
                       "、「" HIY "養老" HIW "」三穴。\n" NOR;

                ap = attack_power(me, "finger");
                dp = defense_power(target, "force");

                if (ap / 2 + random(ap) > dp)
                {
                        msg += HIR "霎時間$n" HIR "只覺得手腕一麻，手中" + wp +
                               HIR "再也拿持不住，脫手掉在地上。\n\n" HIW "緊"
                               "接著";
                        addn("neili", -150, me);
                        weapon->move(environment(target));
                } else
                {
                        msg += CYN "可是$n" CYN "將手中" + wp + NOR + CYN "轉"
                               "動如輪，終于化解了這一招。\n\n" HIW "緊接著";
                        addn("neili", -100, me);
                }
        }

        msg += "$N" HIW "凝氣于指，一式「" HIR "陽關三疊" HIW "」點出，頓時一股"
               "純陽的內力直襲$n" HIW "胸口！\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
                                           HIR "結果$n" HIR "被$N" HIR "一指點中"
                                           HIY + xue_name[random(sizeof(xue_name))] +
                                           HIR "，全身真氣逆流而上，登時嘔出一大"
                                           "口鮮血。\n" NOR);

                addn_temp("sun-finger/die", 1, target);
        } else
        {
                msg += CYN "可是$p" CYN "鎮定自如，全力化解了$P"
                       CYN "這精妙的一指。\n" NOR;
        }

        ap = attack_power(me, "finger");
        dp = defense_power(target, "dodge");

        msg += "\n" HIW "接著$N" HIW "踏前一步，體內真氣迸發，隔空一指勁點$n" HIW
               "而去，指氣縱橫，嗤然作響！\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80,
                                           HIR "結果$n" HIR "被$N" HIR "一指點中"
                                           HIY + xue_name[random(sizeof(xue_name))] +
                                           HIR "，全身真氣逆流而上，登時嘔出一大"
                                           "口鮮血。\n" NOR);

                addn_temp("sun-finger/die", 1, target);
        } else
        {
                msg += CYN "可是$p" CYN "鎮定自如，全力化解了$P"
                       CYN "這精妙的一指。\n" NOR;
        }

        ap = attack_power(me, "finger");
        dp = defense_power(target, "force");

        msg += "\n" HIW "最後$N" HIW "一聲猛喝，單指“嗤”的一聲點出，純陽指力同"
               "時籠罩$n" HIW "全身諸多要穴！\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 90,
                                           HIR "結果$n" HIR "被$N" HIR "一指點中"
                                           HIY + xue_name[random(sizeof(xue_name))] +
                                           HIR "，全身真氣逆流而上，登時嘔出一大"
                                           "口鮮血。\n" NOR);

                addn_temp("sun-finger/die", 1, target);
        } else
        {
                msg += CYN "可是$p" CYN "鎮定自如，全力化解了$P"
                       CYN "這精妙的一指。\n" NOR;
        }

        if( query_temp("sun-finger/die", target) == 3
            && query("neili", target) )
        {
                msg += HIY "\n$n" HIY "被$N" HIY "三指連中，全身真氣渙"
                       "散，宛如黃河決堤，內力登時狂瀉而出。\n\n" NOR;
                set("neili", 0, target);
        }
        me->start_busy(3 + random(2));
        addn("neili", -800, me);
        delete_temp("sun-finger/die", target);
        message_combatd(msg, me, target);

        if( !query("neili", target) )
                tell_object(target, HIC "你只覺丹田內竟似空空如也，一時"
                                    "說不出的難受。\n" NOR);

        return 1;
}
