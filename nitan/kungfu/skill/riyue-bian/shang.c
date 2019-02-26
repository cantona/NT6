// This program is a part of NITAN MudLIB
// shang.c 傷字訣

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "傷字訣"; }
int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「傷字訣」只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對。\n");

        if (me->query_skill("force") < 300)
                return notify_fail("你的內功的修為不夠，不能使用這一絕技！\n");

        if (me->query_skill("riyue-bian", 1) < 180)
                return notify_fail("你的日月鞭法修為不夠，目前不能使用傷字訣！\n");

        if( query("neili", me)<400 )
                return notify_fail("你的真氣不夠，無法使用傷字訣！\n");

        if (me->query_skill_mapped("whip") != "riyue-bian")
                return notify_fail("你沒有激發日月鞭法，不能使用傷字訣！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "$N" HIY "嘿然冷笑，手中的" + weapon->name() +
              HIY "一振，霎時變得筆直，如同流星一般飛刺向$n" + HIY "！\n" NOR;

        ap = attack_power(me, "whip") +
             me->query_skill("force");

        dp = defense_power(target, "parry") +
             target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "whip");
                damage+= query("jiali", me);
                damage+= random(damage);
                addn("neili", -300, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 500,
                                           HIR "只見$p" HIR "一聲慘叫，" + weapon->name() +
                                           HIR "竟然插在$p" + HIR "的身上，創口已經"
                                           "對穿，鮮血飛濺數尺，慘不堪言！\n" NOR);
                me->start_busy(1 + random(2));
        } else
        {
                addn("neili", -100, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "運足內力，奮力擋住了"
                       CYN "$P" CYN "這神鬼莫測的一擊！\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
