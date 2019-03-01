// This is player's own perform (Write by Lonely@nt2)
//Createby易水寒(Rain)atWed Aug 20 00:34:46 2014
// 一刀成狂(yidao)
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "一刀成狂" NOR; }

string *weapon_sk = ({
        "sword", "blade", "staff", "whip", "club", "hammer", "axe"
});

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
        int attack;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if (member_array("blade", weapon_sk) != -1)
        {
                attack = WEAPON_ATTACK;
                if( !objectp(weapon=query_temp("weapon", me) )
                    || query("skill_type", weapon) != "blade" )
                        return notify_fail("你所使用的武器不對，難以施展" + name() + "。\n");
        } else
        {
                attack = UNARMED_ATTACK;
                if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                        return notify_fail(name() + "只能空手使用。\n");
        }

        if ((int)me->query_skill("mad-blade", 1) < 400)
                return notify_fail("你" + to_chinese("mad-blade") + "不夠嫻熟，難以施展" + name() + "。\n");

        if (member_array("blade", weapon_sk) == -1)
        {
                if (me->query_skill_prepared("blade") != "mad-blade")
                        return notify_fail("你沒有準備" + to_chinese("mad-blade") + "，難以施展" + name() + "。\n");
        }

        if( query("neili", me)<300 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N手中武器直直劈出，毫無華麗可言，卻去勢極快，刀未至氣先及，$n呆立當場！" + "\n" + NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                msg += COMBAT_D->do_damage(me, target, attack, damage, 90, HIM "只見$n一聲慘叫，胸口給劈開一個巨大的口子，鮮血洶湧噴出！" + "\n" NOR);
                addn("neili", -200, me);
                me->start_busy(1);
                /*
                if (! target->is_busy())
                        target->start_busy(2);
                */
        } else
        {
                msg += NOR + CYN "$p見勢不妙，抽身急退，險險避過$P的這記殺招，塵土飛揚中，地上裂開了一道大口子！" + "\n" NOR;
                addn("neili", -100, me);
                me->start_busy(2);
        }

        message_sort(msg, me, target);
        return 1;
}
