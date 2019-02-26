// This program is a part of NITAN MudLIB
// wuse.c  無色無相

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "無色無相"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「無色無相」只能在戰鬥中對對手使用。\n");

        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("你必須空手才能使用「無色無相」！\n");

        if (me->query_skill("force") < 100)
                return notify_fail("你的內功的修為不夠，不能使用這一絕技！\n");

        if (me->query_skill("wuxiang-zhi", 1) < 150)
                return notify_fail("你的無相指修為不夠，目前不能使用「無色無相」！\n");

        if( query("neili", me)<400 )
                return notify_fail("你的真氣不夠，無法使用「無色無相」！\n");

        if (me->query_skill_mapped("finger") != "wuxiang-zhi")
                return notify_fail("你沒有激發大力無相指，不能使用「無色無相」！\n");

        msg = HIY "$N" HIY "聚起全身功力，匯聚於右指，縱身而上，"
              HIY "向$n撲去，同時一指劃出，如同流星一般擊向$n" + HIY "！\n" NOR;

        ap = attack_power(me, "finger") + me->query_skill("force");
        dp = defense_power(target, "parry") + target->query_skill("dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "finger");
                addn("neili", -200, me);

                msg += HIR "只見$p" HIR "一聲慘叫，已被點中胸口要穴，"
                       "$p" HIR "只覺得胸口氣血洶湧，全身氣血"
                       "倒流，哇的一聲吐出一口鮮血，苦不堪言！\n" NOR;
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 50);
                me->start_busy(1 + random(2));
        } else
        {
                addn("neili", -100, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "看破了$N" CYN "的企圖，輕輕"
                       CYN "向後飄出數丈，躲過了這一致命的一擊！\n"NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}