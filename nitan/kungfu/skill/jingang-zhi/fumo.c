// This program is a part of NITAN MudLIB
// fumo.c  金剛伏魔決

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "金剛伏魔決"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「金剛伏魔決」只能在戰鬥中對對手使用。\n");

        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("你必須空手才能使用「金剛伏魔決」！\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的內功的修為不夠，不能使用這一絕技！\n");

        if (me->query_skill("jingang-zhi", 1) < 150)
                return notify_fail("你的大力金剛指修為不夠，目前不能使用「金剛伏魔決」！\n");

        if( query("neili", me)<400 )
                return notify_fail("你的真氣不夠，無法使用「金剛伏魔決」！\n");

        if (me->query_skill_mapped("finger") != "jingang-zhi")
                return notify_fail("你沒有激發大力金剛指，不能使用「金剛伏魔決」！\n");

        msg = HIY "$N" HIY "眼中閃過一道青光，匯聚全身功力，右手食指彈出一道"
              HIY "勁氣，劃空而過，如同流星一般擊向$n" + HIY "！\n" NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "finger");
                addn("neili", -200, me);
                msg +=  COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 55,
                                    HIR "只見$p" HIR "一聲慘叫，已被點中胸口要穴，"
                                    "$p" HIR "只覺得胸口氣血洶湧，全身氣血"
                                    "倒流，哇的一聲吐出一口鮮血，苦不堪言！\n" NOR);
                me->start_busy(1 + random(2));
        } else
        {
                addn("neili", -100, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "看破了$N" CYN "的企圖，輕輕"
                       CYN "向後飄出數丈，躲過了這一致命的一擊！\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}