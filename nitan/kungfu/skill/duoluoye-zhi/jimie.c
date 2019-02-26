// This program is a part of NITAN MudLIB
// jumie.c  少林多羅葉指－菩提寂滅

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "菩提寂滅"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「菩提寂滅」只能在戰鬥中對對手使用。\n");

        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("你必須空手才能使用「菩提寂滅」！\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的內功的修為不夠，不能使用這一絕技！\n");

        if (me->query_skill("duoluoye-zhi", 1) < 180)
                return notify_fail("你的多羅葉指修為不夠，目前不能使用「菩提寂滅」！\n");

        if( query("neili", me)<800 || query("max_neili", me)<2500 )
                return notify_fail("你的真氣不夠，無法使用「菩提寂滅」！\n");

        if (me->query_skill_mapped("finger") != "duoluoye-zhi")
                return notify_fail("你沒有激發多羅葉指，不能使用「菩提寂滅」！\n");

        msg = HIB "$N" HIB "運起全身功力，直撲向$n" + HIB "，雙手一圈，用一股內勁" +
              "拖住$n，" + HIB "隨即全力一指戳出，不惜耗費大量真元，力求一擊斃敵！\n" NOR;

        ap = attack_power(me, "finger") + me->query_skill("force", 1);
        dp = defense_power(target, "dodge") + target->query_skill("force", 1);

        damage = damage_power(me, "finger");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -500, me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55,
                                           HIR "只見$p" HIR "一聲慘號，已被$P" +
                                           HIR "一指擊中，一股霸道的內力由$P" +
                                           HIR "的指尖傳來，傷及經脈！\n" NOR);
                me->start_busy(1 + random(2));
        } else
        {
                addn("neili", -200, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "內力深厚，及時擺脱了"
                       CYN "$P" CYN "內力的牽扯，躲開了這一擊！\n" NOR;
        }

        msg += HIR "而$P" + HIR "由於內力提升過度，經脈負荷不" +
               "了，受了不輕的內傷！\n" NOR;

        me->receive_damage("qi", damage / 10);

        message_combatd(msg, me, target);

        return 1;
}