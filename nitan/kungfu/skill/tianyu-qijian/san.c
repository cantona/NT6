// This program is a part of NITAN MudLIB
// san.c  天女散花

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string name() { return "天女散花"; }

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg, pmsg;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「天女散花」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if ((int)me->query_skill("tianyu-qijian", 1) < 100)
                return notify_fail("你的天羽奇劍不夠嫻熟，不會使用。\n");

        if ((int)me->query_skill("xiaowuxiang", 1)<100
                && (int)me->query_skill("bahuang-gong", 1)<100
                && (int)me->query_skill("beiming-shengong", 1)<100)
                return notify_fail("你的逍遙派內功火候不夠。\n");

        if (me->query_skill_mapped("force") != "xiaowuxiang"
                && me->query_skill_mapped("force") != "bahuang-gong"
                && me->query_skill_mapped("force") != "beiming-shengong")
                return notify_fail("你沒有運用逍遙派內功！\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在內力太弱，不能使用「天女散花」。\n");

        msg = CYN "\n$N凝神息氣，手腕疾抖，挽出千萬個劍花，舖天蓋地飛向$n。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                damage+= query("jiali", me);

                addn("neili", -200, me);
                pmsg = HIR "\n只見$N劍花聚為一線，穿向$n。\n$n只覺一股熱流穿心而過，喉頭一甜，鮮血狂噴而出！\n\n" NOR;

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50, pmsg);
                me->start_busy(2);
        } else
        {
                msg += CYN "可是$p猛地向前一躍,跳出了$P的攻擊范圍。\n" NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}
