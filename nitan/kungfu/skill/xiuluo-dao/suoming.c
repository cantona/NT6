// This program is a part of NITAN MudLIB
// suoming.c 修羅索命

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "修羅索命"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「修羅索命」只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的內功的修為不夠，不能使用這一絕技！\n");

        if (me->query_skill("xiuluo-dao", 1) < 135)
                return notify_fail("你的修羅刀法修為不夠，目前不能使用修羅索命！\n");

        if( query("neili", me)<250 )
                return notify_fail("你的真氣不夠，不能使用修羅索命！\n");

        if (me->query_skill_mapped("blade") != "xiuluo-dao")
                return notify_fail("你沒有激發修羅刀法，不能使用修羅索命！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIC "$N" HIC "臉上殺氣大盛，一振手中的" + weapon->name() +
              HIC "，唰唰數刀將$n" + HIC "團團裹住！\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                addn("neili", -180, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           HIR "就聽見$p" HIR "慘叫連連，一陣陣血雨自" HIR
                                           "亮白的刀光中濺出！\n" NOR);
                me->start_busy(1 + random(2));
        } else
        {
                addn("neili", -60, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "眼明手快，只聽叮叮當當響起了一串"
                       CYN "刀鳴，$p" CYN "將$P" CYN "的招式全部擋開！\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
