// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "斂心令" NOR; }

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        skill = me->query_skill("shenghuo-ling", 1);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if (! objectp(weapon = query_temp("weapon", me)) ||
            (string)query("skill_type", weapon) != "sword")
                return notify_fail("你使用的兵器不對，不能使用聖火令法之" + name() + "。\n");

        if (skill < 150)
                return notify_fail("你的聖火令法等級不夠, 不能使用聖火令法之" + name() + "。\n");

        if (query("max_neili", me) < 1600 )
                return notify_fail("你的內力修為不足，不能使用聖火令法之" + name() + "。\n");

        if (query("neili", me) < 350 )
                return notify_fail("你的內力不夠，不能使用聖火令法之" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "shenghuo-ling")
                return notify_fail("你沒有激發聖火令法，不能使用聖火令法之" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "$N" HIW "一個筋斗猛翻至$n" HIW "跟前，陡然使出聖火"
              "令法之斂心令，手中" + weapon->name() + NOR + HIW "忽伸"
              "忽縮，招式詭異無比。\n" NOR;

        damage = damage_power(me, "sword");

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");


        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -300, me);
                me->start_busy(3);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK,
                       damage, 50, (: final, me, target, damage :));

        }
        else
        {
                addn("neili", -100, me);
                msg += CYN "$n" CYN "見眼前寒光顫動，連忙振作精神勉強"
                      "抵擋，向後疾退數步，好不容易閃在了$N" CYN "攻"
                      "擊範圍之外。\n" NOR;
                me->start_busy(4);
        }
        message_combatd(msg, me, target);
        return 1;
}

string final(object me, object target, int damage)
{

       target->receive_damage("jing", damage / 2, me);
       target->receive_wound("jing", damage / 4, me);
       target->start_busy(1);

       return HIR "$n" HIR "只見眼前寒光顫動，突"
              "然$N" HIR "雙手出現在自己眼前，兩處太陽穴頓"
              "時一陣劇痛。\n" NOR;
}
