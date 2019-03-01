#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "<絕招名>" NOR; }

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

        if (member_array("BASE_SKILL", weapon_sk) != -1)
        {
                attack = WEAPON_ATTACK;
                if( !objectp(weapon=query_temp("weapon", me) )
                    || query("skill_type", weapon) != "BASE_SKILL" )
                        return notify_fail("你所使用的武器不對，難以施展" + name() + "。\n");
        } else
        {
                attack = UNARMED_ATTACK;
                if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                        return notify_fail(name() + "只能空手使用。\n");
        }

        if ((int)me->query_skill("SKILL", 1) < 400)
                return notify_fail("你" + to_chinese("SKILL") + "不夠嫻熟，難以施展" + name() + "。\n");

        if (member_array("BASE_SKILL", weapon_sk) == -1)
        {
                if (me->query_skill_prepared("BASE_SKILL") != "SKILL")
                        return notify_fail("你沒有準備" + to_chinese("SKILL") + "，難以施展" + name() + "。\n");
        }

        if( query("neili", me)<300 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "<PFM發招描述>" + "\n" + NOR;

        ap = attack_power(me, "BASE_SKILL");
        dp = defense_power(target, "parry");

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = damage_power(me, "BASE_SKILL");
                msg += COMBAT_D->do_damage(me, target, attack, damage, 90, HIM "<PFM打中描述>" + "\n" NOR);
                addn("neili", -200, me);
                me->start_busy(1);
                /*
                if (! target->is_busy())
                        target->start_busy(2);
                */
        } else
        {
                msg += NOR + CYN "<PFM失誤描述>" + "\n" NOR;
                addn("neili", -100, me);
                me->start_busy(2);
        }

        message_sort(msg, me, target);
        return 1;
}
