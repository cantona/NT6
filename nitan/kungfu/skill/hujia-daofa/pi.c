// pi.c 開天辟地

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "開天辟地"; }

int perform(object me, object target)
{
        object weapon,weapon2;
        int damage,i;
        string msg,str;
        int ap, dp;
        int n;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail("「開天辟地」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("運用「開天劈地」手中必須有刀！\n");

        if ((int)me->query_skill("hujia-daofa", 1) < 600)
                return notify_fail("你的胡家刀法不夠嫻熟，不會使用「開天辟地」。\n");

        if ((int)me->query_skill("force") < 650)
                return notify_fail("你的內功修為不夠高。\n");

        if( query("neili", me)<800 )
                return notify_fail("你現在內力太弱，不能使用「開天劈地」。\n");

        msg = HIC "$N" HIC "一聲長笑，雙手緊握" + weapon->name() +
              HIC "刀柄，長吸一口氣，全力向$n" HIC "迅猛劈去！\n\n"NOR;

        //if( query_temp("hu/freeze", me) )
        if (query_temp("lengyue-shengong_freeze", target))
        {
                msg += HIW + weapon->name() +
                HIW "寒氣逼人，刀身撕裂空氣，片片雪花飄落，刀未至氣先及，$n" HIW "眉毛都蒙上了薄薄白霜！\n\n"NOR;
        }

        ap = attack_power(me, "blade") + me->query_skill("force");
        if (living(target))
                 dp = target->query_skill("force") + defense_power(target, "parry");
        else     dp = 0;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                damage+=query("jiali", me);
                addn("neili", -damage/2, me);
                if( !objectp(weapon2=query_temp("weapon", target)) )
                {
                        /*
                        target->receive_damage("qi",damage,me);
                        target->receive_wound("qi",damage/2 + random(damage/2),me);
                        msg += HIR "只見$n" HIR "一聲慘叫，胸口給"
                                "劈開一個巨大的口子，鮮血洶湧噴出！\n"NOR;
                        if( query_temp("hu/freeze", me) )
                        {
                                damage /= 3;
                                target->receive_damage("qi",damage,me);
                                target->receive_wound("qi",damage/2 + random(damage/2),me);
                                msg += HIR "\n$n" HIR "身形搖晃間，感覺到"
                                        + weapon->name() + HIR +
                                        "上一陣刺骨的寒氣侵入體內，復又噴出一口鮮血！\n" NOR;
                        }
                        */
                        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                                       HIR "只見$n" HIR "一聲慘叫，胸口給"
                                                       "劈開一個巨大的口子，鮮血洶湧噴出！\n" NOR);

                        if (query_temp("lengyue-shengong_freeze", target))
                                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 33,
                                                           HIB "\n$n" HIB "身形搖晃間，感覺到"
                                                           + weapon->name() + HIB +
                                                           "上一陣刺骨的寒氣侵入體內，復又噴出"
                                                           "一口鮮血！\n" NOR);
                } else
                {
                        /*
                        msg += HIR "$n" HIR "見狀不妙，連忙舉起" + weapon2->name() + HIR +
                                "抵擋，在$N這霸氣無邊的一招下，" + weapon2->name() + HIR +
                                "給震成碎片！\n" NOR;
                        for (i = 0;i < 2 + random(5);i++)
                        {
                                msg += HIB "碎片四散飛濺，射中了$n的身體！\n" NOR;
                                target->receive_damage("qi",damage/7,me);
                                        target->receive_wound("qi",damage/15 + random(damage/15),me);
                        }
                        msg += HIR + weapon->name() + HIR "余勢未盡，又劈入了$n" + HIR +
                                "的胸口，$n遭此重創，鮮血狂噴而出！\n" NOR;

                        if( !weapon2->is_item_make() )
                        {
                                weapon2->set_name("碎裂的"+query("name", weapon2));
                                weapon2->move(environment(target));
                                set("value", 0, weapon2);
                                set("weapon_prop", 0, weapon2);
                        }
                        else
                                weapon2->move(environment(target));
                        */
                        if (weapon2->is_item_make() || weapon2->query("damage") > 800 ||
                            weapon2->query("skill_type") == "hammer")
                                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                                           HIG "$p" HIG "橫過" + weapon2->name() + HIG "試圖招架，"
                                                           HIG "怎奈這刀氣如此犀利，透過" + weapon2->name() +
                                                           HIG "直震得$p" HIG "狂吐鮮血，五臟六腑都要翻轉過來！\n\n" NOR);
                        else
                        {
                                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                                           HIR "$n" HIR "見狀不妙，連忙舉起" +
                                                           weapon2->name() + HIR + "抵擋，在$N" HIR
                                                           "這霸氣無雙的一招下，" + weapon2->name() +
                                                           HIR "給震成碎片！\n\n" NOR);
                                n = 2 + random(5);
                                for (i = 0; i < n; i++)
                                {
                                        msg += (random(2) ? HIB : HIC) + "碎片四散飛濺，射入了$n的身體！\n" NOR;

                                        target->receive_damage("qi", damage / 7, me);
                                                target->receive_wound("qi",damage / 15 + random(damage / 15), me);
                                }

                                msg += "\n" + HIY + weapon->name() + HIY "余勢未盡，又劈入了$n" + HIY +
                                        "的胸口，$n遭此重創，鮮血狂噴而出！\n" NOR;

                                weapon2->set_name("碎裂的" + weapon2->query("name"));
                                weapon2->move(environment(target));
                                weapon2->set("value", 0);
                                weapon2->set("weapon_prop", 0);
                        }
                        target->reset_action();
                        target->receive_damage("qi",damage/2,me);
                                        target->receive_wound("qi",damage/4 + random(damage/4),me);

                        /*
                        if( query_temp("hu/freeze", me) )
                        {
                                damage /= 4;
                                target->receive_damage("qi",damage,me);
                                target->receive_wound("qi",random(damage),me);
                                msg += HIR "\n$n" HIR "身形搖晃間，感覺到"
                                        + weapon->name() + HIR +
                                        "上一陣刺骨的寒氣侵入體內，復又噴出一口鮮血！\n" NOR;
                        }
                        */
                        if (target->query_temp("lengyue-shengong_freeze"))
                                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 200,
                                                           HIB "\n$n" HIB "身形搖晃間，感覺到"
                                                           + weapon->name() + HIB +
                                                           "上一陣刺骨的寒氣侵入體內，復又噴出"
                                                           "一口鮮血！\n" NOR);
                }
                /*
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "( $n"+str+" )\n";
                */
                me->start_busy(3);
                if (! target->is_busy()) target->start_busy(1 + random(2));
        } else
        {
                msg += HIY "$n" HIY "見勢不妙，抽身急退，險險避過$N"
                       HIY "的這記開天辟地，塵土飛揚中，地上裂開了一道大口子！\n"NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
