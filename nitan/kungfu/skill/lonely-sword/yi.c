// yi.c 劍意

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "劍意"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("你只能對戰鬥中的對手使用絕招。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("無劍如何運用劍意？\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不夠，無法使用劍意！\n");

        if ((int)me->query_skill("lonely-sword", 1) < 120)
                return notify_fail("你的獨孤九劍還不到家，無法使用劍意！\n");

        if (me->query_skill_mapped("sword") != "lonely-sword")
                return notify_fail("你沒有激發獨孤九劍，無法使用劍意！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        switch (random(3))
        {
        case 0:
                msg = HIM "$N" HIM "一劍刺出，連自已也不知道要刺往何處。\n" NOR;
                break;

        case 1:
                msg = HIM "$N" HIM "隨手揮洒手中的" + weapon->name() +
                       HIM "，漫無目的，不成任何招式。\n" NOR;
                break;

        default:
                msg = HIM "$N" HIM "斜斜刺出一劍，準頭之差，令人匪夷所思。\n" NOR;
                break;
        }

        ap = attack_power(me, "sword") + me->query_skill("sword-cognize");
        dp = defense_power(target, "parry") + target->query_skill("sword-cognize");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -180, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 200,
                                           HIR "$n" HIR "全然無法領會$P"
                                           HIR "這莫名其妙的招數，一個疏神，登時受創！\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += CYN "$n" CYN "淡然處之，並沒有將$P"
                       CYN "此招放在心上，隨手架開，不漏半點破綻。\n" NOR;
                addn("neili", -60, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}