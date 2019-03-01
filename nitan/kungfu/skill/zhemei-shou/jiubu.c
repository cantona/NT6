// This program is a part of NITAN MudLIB
// jiubu.c 九部式

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "九部式"; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail("「九部式」只能對戰鬥中的對手使用。\n");

        if ((int)me->query_skill("zhemei-shou", 1) < 120)
                return notify_fail("你的折梅手法不夠嫻熟，不會使用「九部式」。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的內功修為不夠高，難以運用「九部式」。\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在真氣不夠，不能使用「九部式」。\n");

        if (me->query_skill_mapped("hand") != "zhemei-shou")
                return notify_fail("你沒有激發天山折梅手，不能使用「九部式」。\n");

        msg = HIC "$N" HIC "雙手虛虛實實的抓向$n"
              HIC "的要害，身法縹緲，手式奇特，令人難以捉摸。\n" NOR;

        ap=attack_power(me,"hand")+me->query_str()*20;
        dp=defense_power(target,"dodge")+target->query_dex()*20;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "hand");
                damage+= query("jiali", me);
                addn("neili", -100, me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                           HIR "$p" HIR "一個閃避不及，結果被$P"
                                           HIR "抓了個正中，渾身內息不由得一滯，氣血翻湧。\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += HIC "可是$p" HIC "身手敏捷，巧妙的躲過了$P"
                       HIC "的攻擊！\n"NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}