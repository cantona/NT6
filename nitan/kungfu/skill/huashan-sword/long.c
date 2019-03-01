// This program is a part of NITAN MudLIB
// feilong.c 華山劍法「天外飛龍」

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "天外飛龍" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「天外飛龍」只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("不拿劍怎麼使用「天外飛龍」？\n");

        if ((int)me->query_skill("huashan-sword", 1) < 150 )
                return notify_fail("你華山劍法不夠嫻熟，使不出「天外飛龍」。\n");

        if ((int)me->query_skill("force") < 150 )
                return notify_fail("你內功火候不夠，使不出「天外飛龍」。\n");

        if( query("neili", me)<400 )
                return notify_fail(HIC"你現在真氣不夠，無法將「天外飛龍」使完！\n"NOR);

        if (me->query_skill_mapped("sword") != "huashan-sword")
                return notify_fail("你沒有激發華山劍法，無法使用「天外飛龍」。\n");

        msg = HIC "$N" HIC "心念電閃，一提內力，勒手仗劍，運勁于臂，呼"
              "的一聲向$n" HIC "擲了出去，\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");
        if (ap > dp / 2 * 3 && ap / 2 + random(ap) > dp)
        {
                me->start_busy(3);
                damage = target->query("max_qi");
                //damage = damage_power(me, "sword") * 3 / 2;
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           HIC "$n疾忙躍起，但劍如電閃，只覺一陣劇痛，劍刃"
                                           "攔腰而過，鮮血飛濺，皮肉卷起！\n" NOR);
                addn("neili", -400, me);
        } else
        {
                me->start_busy(3);
                msg += CYN "然而$n" CYN "輕輕一笑，側身伸指，正彈"
                       "在$N" CYN "的劍脊上，劍斜飛落地。\n" NOR;
                addn("neili", -400, me);
        }

        weapon->move(environment(me));
        message_combatd(msg, me, target);
        return 1;
}