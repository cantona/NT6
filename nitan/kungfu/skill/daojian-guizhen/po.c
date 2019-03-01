//modify by gladiator

#include <ansi.h>
#include <combat.h>

string name() { return HIY "破" HIG "定" HIC "軍" HIW "山" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon, weapon2;
        int damage, i, n;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword"
                 && query("skill_type", weapon) != "blade" )
                        return notify_fail("你所使用的武器不對，難以施展" + name() + "。\n");

        if (me->query_skill("daojian-guizhen", 1) < 300)
                return notify_fail("你的刀劍歸真不夠嫻熟，不會使用" + name() + "。\n");

        if (me->query_skill("force") < 350)
                return notify_fail("你的內功修為不夠高。\n");

        if( query("neili", me)<800 )
                return notify_fail("你現在內力太弱，不能使用" + name() + "。\n");


        msg = HIC "$N" HIC "大吼一聲，雙手橫握" + weapon->name() +
              HIC "，長吸一口氣，全力向$n" HIC "迅猛劈去！\n\n" NOR;


        if( query_temp("powerup", me) )
        {
                msg += HIW + weapon->name() +
                HIW "無邊的殺氣撕裂空氣，武器上所帶的寒氣仿佛可以冰凍一切，"
                "刃未至而氣先及，$n" HIW "眉毛都蒙上了薄薄白霜！\n\n" NOR;
        }

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");
        if (ap / 2 + random(ap / 2) > dp)
        {
                damage = damage_power(me, "blade");
                damage+=query("jiali", me);

                addn("neili", -600, me);

                if( !objectp(weapon2=query_temp("weapon", target)) )
                {
                        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
                                                       HIR "只見$n" HIR "一聲慘叫，胸口給"
                                                       "劈開一個巨大的口子，鮮血洶湧噴出！\n" NOR);

                        if (me->query_skill("daojian-guizhen", 1) > 320)
                                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                                           HIB "\n$n" HIB "身形搖晃間，感覺到"
                                                           + weapon->name() + HIB +
                                                           "上一陣刺骨的寒氣侵入體內，復又噴出"
                                                           "一口鮮血！\n" NOR);

                        if (me->query_skill("daojian-guizhen", 1) > 350)
                                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                                           HIY "\n$n" HIY "再也堅持不住，幾欲暈倒"
                                                           "$N將手中利刃在地上一拖，$N順勢反手往又上"
                                                           "撩了一招，$n毫無防御，傷口再次擴大，\n"
                                                           "又是一股血柱直噴而出！\n" NOR);

                } else
                {
                        if( weapon2->is_item_make() || query("damage", weapon2)>800 ||
                            query("skill_type", weapon2) == "hammer" )
                                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90,
                                                           HIG "$p" HIG "橫過" + weapon2->name() + HIG "試圖招架，"
                                                           HIG "怎奈這刀氣如此犀利，透過" + weapon2->name() +
                                                           HIG "直震得$p" HIG "狂吐鮮血，五臟六腑都要翻轉過來！\n\n" NOR);
                        else
                        {
                                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70,
                                                           HIR "$n" HIR "見狀不妙，連忙舉起" +
                                                           weapon2->name() + HIR + "抵擋，在$N" HIR
                                                           "這霸氣無雙的一招下，" + weapon2->name() +
                                                           HIR "給震成碎片！\n\n" NOR);
                                n = 3 + random(3);
                                for (i = 0; i < n; i++)
                                {
                                        msg += (random(2) ? HIB : HIC) + "碎片四散飛濺，射入了$n的身體！\n" NOR;

                                        target->receive_damage("qi", damage / 7, me);
                                                target->receive_wound("qi",damage / 15 + random(damage / 15), me);
                                }

                                msg += "\n" + HIY + weapon->name() + HIY "余勢未盡，又劈入了$n" + HIY +
                                        "的胸口，$n遭此重創，鮮血狂噴而出！\n" NOR;

                                if( query("material", weapon2) != "tian jing" && random(2) == 1 )
                                {
                                        weapon2->set_name("碎裂的"+query("name", weapon2));
                                        weapon2->move(environment(target));
                                        set("value", 0, weapon2);
                                        set("weapon_prop", 0, weapon2);
                                } else
                                {
                                        weapon2->move(environment(target));
                                        addn("consistence", - 20, weapon2);
                                }
                        }

                        target->reset_action();
                        target->receive_damage("qi", damage / 2, me);
                                               target->receive_wound("qi",
                                               damage / 4 + random(damage / 4), me);

                        if( query_temp("powerup", me) )
                                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 25,
                                                           HIB "\n$n" HIB "身形搖晃間，感覺到"
                                                           + weapon->name() + HIB +
                                                           "上一陣刺骨的寒氣侵入體內，復又噴出"
                                                           "一口鮮血！\n" NOR);
                }
                me->start_busy(3);
                target->start_busy(1 + random(2));
        } else
        {
                msg += HIY "$n" HIY "見勢不妙，抽身急退，險險避過$N"
                       HIY "的殺招，塵土飛揚中，地上裂開了一道大口子！\n"
                       HIR "$N的頭上冒出一顆顆豆大的冷汗，一時之間也無法使出反擊的招式！\n" NOR;
                addn("neili", -100, me);
                me->start_busy(3);
                if( !target->is_busy() )
                        target->start_busy(1 + random(2));
        }

        message_combatd(sort_msg(msg), me, target);

        return 1;
}