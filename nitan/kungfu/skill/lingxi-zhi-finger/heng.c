// This is player's own perform (Write by Lonely@nt2)
//Createby小妖(Sata)atTue May 10 15:39:34 2011
// 橫掃千軍(heng)
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "橫掃千軍" NOR; }

string *weapon_sk = ({
        "sword", "blade", "staff", "whip", "club", "hammer", "axe"
});

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, attack_time;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if (member_array("finger", weapon_sk) != -1)
        {
                if( !objectp(weapon=query_temp("weapon", me) )
                    || query("skill_type", weapon) != "finger" )
                        return notify_fail("你所使用的武器不對，難以施展" + name() + "。\n");
        } else
        {
                if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                        return notify_fail(name() + "只能空手使用。\n");
        }

        if ((int)me->query_skill("lingxi-zhi-finger", 1) < 400)
                return notify_fail("你" + to_chinese("lingxi-zhi-finger") + "不夠嫻熟，難以施展" + name() + "。\n");

        if (member_array("finger", weapon_sk) == -1)
        {
                if (me->query_skill_prepared("finger") != "lingxi-zhi-finger")
                        return notify_fail("你沒有準備" + to_chinese("lingxi-zhi-finger") + "，難以施展" + name() + "。\n");
        }

        if( query("neili", me)<300 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "$N一聲怒嚎，雙手指氣迸發，頓時攜着雷霆萬鈞之勢猛貫向$n。第一指！$N一聲怒嚎，雙手指氣迸發，頓時攜着雷霆萬鈞之勢猛貫向$n。第二指！$N一聲怒嚎，雙手指氣迸發，頓時攜着雷霆萬鈞之勢猛貫向$n。第三指！$N一聲怒嚎，雙手指氣迸發，頓時攜着雷霆萬鈞之勢猛貫向$n。第四指！$N一聲怒嚎，雙手指氣迸發，頓時攜着雷霆萬鈞之勢猛貫向$n。第五指！" + "\n" + NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "dodge");
        attack_time = 6;

        if (ap * 2 / 3 + random(ap) > dp)
        {
                msg += HIM "只見$n一聲慘叫，胸口給洞開一個拇指粗的血洞，鮮血洶湧噴出！" + "\n" NOR;
                count = ap / 10;
                addn_temp("apply/attack", count, me);
                addn_temp("apply/damage", count, me);
        } else
        {
                msg += NOR + CYN "$p見勢不妙，抽身急退，險險避過$P的這記殺招，塵土飛揚中，地上酣然開了一個深洞！" + "\n" NOR;
                count = 0;
        }

        message_sort(msg, me, target);

        attack_time+=query("jieti/times", me)*2;
        if (attack_time > 13)
                attack_time = 13;

        addn("neili", -attack_time*20, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) && ! target->is_busy()) target->start_busy(1);

                COMBAT_D->do_attack(me, target, (member_array("finger", weapon_sk) == -1 ? 0 : weapon), 0);
        }
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count, me);
        me->start_busy(3 + random(attack_time/ 3));

        return 1;
}
