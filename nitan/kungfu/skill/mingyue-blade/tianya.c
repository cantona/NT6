// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIY "天涯"HIW"明月" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int ap, dp, wn;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if ((int)me->query_skill("mingyue-blade", 1) < 200)
                return notify_fail("你天涯明月刀不夠嫻熟，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 280 )
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的內力修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<600 )
                return notify_fail("你現在真氣不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "mingyue-blade")
                return notify_fail("你沒有激發天涯明月刀，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        wn = weapon->name();

        msg = HIC "$N" HIC "手中的 " + weapon->name() +  HIC "悄然探出，變化中突然收勁，$n一時不查，身形頓時被$N的" + weapon->name() + HIC"吸住，\n"
                  "只聽$N一聲輕蔑的哼聲，" + weapon->name() + HIC"從$n頭頂位置閃電下劈！\n "NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "blade");
                damage+= query("jiali", me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 300,
                                           HIR "$n" HIR "頓時大驚失色，呆若木雞,避無可避，"
                                           "頓時被砍得血肉模糊，鮮血崩流！\n" NOR);
                addn("neili", -500, me);
                addn("shen", -100, me);
        } else
        {
                me->start_busy(3);
                msg += HIC "$p" HIC "見$P來勢洶湧，心知絕不可擋，當即向後橫移數尺，終於躲閃開來。\n" NOR;
                addn("neili", -400, me);
        }
        message_combatd(msg, me, target);
        return 1;
}
