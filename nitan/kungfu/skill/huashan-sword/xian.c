// This program is a part of NITAN MudLIB
// feilong.c 華山劍法「奪命連環三仙劍」

#include <ansi.h>
#include <combat.h>

string name() { return HIM "奪命連環三仙劍" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int ap, dp, fp, pp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對！\n");

        if( query_temp("perform", me) == 1 ||
            query_temp("perform2", me) == 1 ||
            query_temp("perform3", me) == 1 )
                return notify_fail("你現在正用著「劍芒」呢。\n");


        if ((int)me->query_skill("huashan-sword", 1) < 160)
                return notify_fail("你華山劍法不夠嫻熟，無法施展" + name() + "。\n");

        if ((int)me->query_skill("dodge", 1) < 160)
                return notify_fail("你輕功修為不夠，無法施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在真氣不夠，無法施展" + name() + "！\n");

        if (me->query_skill_mapped("sword") != "huashan-sword")
                return notify_fail("你沒有激發華山劍法，無法使用" + name() + "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        addn("neili", -280, me);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");
        fp = defense_power(target, "force");
        pp = defense_power(target, "parry");
        damage = damage_power(me, "sword");

        message_combatd(HIW "\n$N" HIW "長嘯一聲，手中" + weapon->name() + HIW "隨即不停轉動，洶湧而\n"
                        "出，正是華山劍宗絕技「" HIM "奪命連環三仙劍" HIW "」，但是" + weapon->name() + HIW
                        "\n劍鋒突變，一劍頓時化為三劍，襲向$n" HIW "……\n" NOR, me, target);

        msg = HIM "$N" HIM "將內力全都運到了劍上，呼的一劍，當頭直劈。\n" NOR;
        if (ap / 2 + random(ap) < dp)
                msg += CYN "$n" CYN "斜身閃開。\n" NOR;
        else
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40 + random(20),
                                           HIR "$n" HIR "急忙後退，竟然躲避不及，被$N"
                                           HIR "這一劍震得口吐鮮血，接連後退。\n" NOR);
        }

        msg += HIM "\n$N" HIM "圈轉" + weapon->name() + HIM "，攔腰橫削，劍勢恢弘，劍氣縱橫，令人匪夷所思。\n" NOR;
        if (ap / 2 + random(ap) < fp)
                msg += CYN "$n" CYN "縱身從劍上越過。\n" NOR;
        else
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40 + random(20),
                                           HIR "此招來勢當真快及，$n" HIR "哪裡來得及閃"
                                           "避招架？只見$N" HIR "劍光閃過，$n"
                                           HIR "腰間霎時鮮血淋漓！\n" NOR);
        }

        msg += HIM "\n$N" HIM "長劍反撩，疾刺$p" HIM "後心，劍法之快，部位之準，當真聞所未聞。\n" NOR;
        if (ap / 2 + random(ap) < pp)
                msg += CYN "$n" CYN "身在空中，不及變招，只能揮出一招，正擊中$N"
                       CYN "劍上，略一借力，飄然避去。\n" NOR;
        else
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50 + random(20),
                                           HIR "$n" HIR "身在空中，哪裡來得及變招？只見$N"
                                           HIR "此劍掠過，$n" HIR "大聲慘呼，鮮血四下飛濺！\n" NOR);
        }

        me->start_busy(4);
        message_combatd(msg, me, target);
        return 1;
}
