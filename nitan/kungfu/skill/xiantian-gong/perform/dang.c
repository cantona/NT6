// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "神威浩盪" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon, cloth;
        int ap, dp, damage;
        string wp;
        string cl;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("xiantian-gong", 1) < 240)
                return notify_fail("你的先天功修為不夠，難以施展" + name() + "。\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("你的內力修為不足，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("unarmed") != "xiantian-gong")
                return notify_fail("你沒有激發先天功為拳腳，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("force") != "xiantian-gong")
                return notify_fail("你沒有激發先天功為內功，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("unarmed") != "xiantian-gong")
                return notify_fail("你沒有準備使用先天功，難以施展" + name() + "。\n");

        if( query("neili", me)<800 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "只見$N" HIW "雙目精光四射，雙掌陡然一振，將體內積蓄的"
              "先天真氣雲貫推出，頓時呼嘯\n聲大作，先天勁道層層疊疊，宛如"
              "濤浪般湧向$n" HIW "。\n" NOR;

        ap = attack_power(me, "unarmed") + me->query_skill("force");
        dp = defense_power(target, "parry") + target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = 0;
                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        me->start_busy(2);
                        msg += HIR "便在$n" HIR "微微一愣間，$N" HIR "罡風已然"
                               "及體，$p" HIR "一聲哀嚎，全身骼絡盡數斷裂。\n"
                               NOR "( $n" RED "受傷過重，已經有如風中殘燭，隨"
                               "時都可能斷氣。" NOR ")\n";
                        damage = -1;
                } else
                {
                        me->start_busy(2);
                        damage = damage_power(me, "unarmed");
                        damage+= query("jiali", me);
                        addn("neili", -400, me);
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK,
                                                   damage, 90, HIR "$N" HIR "的"
                                                   "罡勁登時瓦解了$n" HIR "的護"
                                                   "體真氣，$p" HIR "真元受損，"
                                                   "接連噴出數口鮮血。\n" NOR);

                        if( objectp(weapon=query_temp("weapon", target) )
                            && query("stable", weapon)<100
                            && ap / 3 + random(ap) > dp)
                        {
                                wp = weapon->name();
                                msg += HIW "只聽“鏘”的一聲脆響，$n" HIW "手"
                                       "中的" + wp + HIW "在$N" HIW "內力激盪"
                                       "下應聲而碎，脫手跌落在地上。\n" NOR;
                                addn("neili", -150, me);
                                set("consistence", 0, weapon);
                                weapon->move(environment(target));
                        } else
                        if( objectp(cloth=query_temp("armor/armor", target) )
                            && query("stable", cloth)<100
                            && ap / 3 + random(ap) > dp)
                        {
                                cl = cloth->name();
                                msg += HIW "只聽“轟”的一聲悶響，$n" HIW "身"
                                       "著的" + cl + HIW "在$N" HIW "內力激盪"
                                       "下應聲而裂，化成一塊塊碎片。\n" NOR;
                                addn("neili", -150, me);
                                set("consistence", 0, cloth);
                                cloth->move(environment(target));
                        } else

                        if( objectp(cloth=query_temp("armor/cloth", target) )
                            && query("stable", cloth)<100
                            && ap / 3 + random(ap) > dp)
                        {
                                cl = cloth->name();
                                msg += HIW "只聽“轟”的一聲悶響，$n" HIW "身"
                                       "著的" + cl + HIW "在$N" HIW "內力激盪"
                                       "下應聲而碎，化成一塊塊碎片。\n" NOR;
                                addn("neili", -150, me);
                                set("consistence", 0, cloth);
                                cloth->move(environment(target));
                        }
                }
        } else
        {
                me->start_busy(3);
                addn("neili", -120, me);
                msg += CYN "可是$p" CYN "知道$P" CYN "這招的厲"
                       "害，不敢硬接，當即斜躍躲避開來。\n" NOR;
        }
        message_combatd(msg, me, target);

        if (damage < 0)
                target->die(me);

        return 1;
}