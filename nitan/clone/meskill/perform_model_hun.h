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
        int count, damage;
        int attack_time;
        int attack, i;

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

        if( query("neili", me)<500 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "<PFM發招描述>" + "\n" + NOR;

        ap = attack_power(me, "BASE_SKILL");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "BASE_SKILL");
                msg += COMBAT_D->do_damage(me, target, attack, damage, 80, HIM "<PFM打中描述>" + "\n" NOR);
                addn("neili", -200, me);

                /*
                if (! target->is_busy())
                        target->start_busy(2);
                */
        } else
        {
                msg += NOR + CYN "<PFM失誤描述>" + "\n" NOR;
                addn("neili", -100, me);
        }

        message_sort(msg, me, target);

        msg = HIW "$N" HIW "餘勢未盡，招式陡然變得凌厲無比，一轉念間已然攻出數招。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 20;
                msg += HIR "$n" HIR "見$P" HIR "來勢迅猛之極，一時不知該如"
                       "何作出抵擋，竟呆立當場。\n" NOR;
        } else
        {
                msg += HIY "$n" HIY "見$p" HIY "來勢迅猛之極，甚難防備，連"
                       "忙振作精神，小心抵擋。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);

        attack_time = 3;
        attack_time+=query("jieti/times", me)*2;
        if (attack_time > 8)
                attack_time = 8;

        addn("neili", -attack_time*20, me);

        addn_temp("apply/attack", count, me);
        addn_temp("apply/damage", count, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me, target, (member_array("BASE_SKILL", weapon_sk) == -1 ? 0 : weapon), 0);
        }
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count, me);
        me->start_busy(3 + random(attack_time/ 3));
        return 1;
}
