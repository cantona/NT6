// This program is a part of NITAN MudLIB
// zhao.c 佛光普照

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "佛光普照"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「佛光普照」只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "staff" )
                return notify_fail("你使用的武器不對。\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的內功的修為不夠，不能使用這一絕技！\n");

        if (me->query_skill("pudu-zhang", 1) < 135)
                return notify_fail("你的普渡杖法修為不夠，目前不能使用佛光普照！\n");

        if( query("neili", me)<1000 )
                return notify_fail("你的真氣不夠，不能使用佛光普照！\n");

        if (me->query_skill_mapped("staff") != "pudu-zhang")
                return notify_fail("你沒有激發普渡杖法，不能使用佛光普照！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "縱聲長笑，揮動手中的" + weapon->name() +
              HIY "，如泰山一般壓向$n" + HIY "，令人嘆為觀止！\n" NOR;

        ap=attack_power(me,"staff")+query("max_neili", me)/10;
        dp=defense_power(target,"force")+query("max_neili", target)/10;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "staff");
                addn("neili", -250, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "只見$p" HIR "悶哼一聲，連叫都叫"
                                           "不出來，身子飛跌出去，重重的摔倒在地上！\n" NOR);
                me->start_busy(1 + random(2));
        } else
        {
                addn("neili", -60, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "運足內力，奮力擋住了"
                       CYN "$P" CYN "這驚天動地的一擊！\n"NOR;
                me->start_busy(2+random(1));
        }
        message_combatd(msg, me, target);

        return 1;
}
