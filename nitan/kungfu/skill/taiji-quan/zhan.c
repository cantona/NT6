// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "粘字訣" NOR; }

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        skill = me->query_skill("taiji-quan", 1);

        if (skill < 150)
                return notify_fail("你的太極拳等級不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("cuff") != "taiji-quan")
                return notify_fail("你沒有激發太極拳，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "$N" HIW "連消帶打，雙手成圓形擊出，這"
              "正是太極拳「圓轉不斷」四字的精意。只\n見$N"
              HIW "隨即平圈、立圈、正圈、斜圈，一個跟着一"
              "個，一個個太極圓圈頓時籠\n罩$n" HIW "四面"
              "八方。\n" NOR;

        ap = attack_power(me,"cuff");
        dp = defense_power(target,"parry");
        if (ap / 2 + random(ap * 4 / 3) > dp)
        {
                addn("neili", -100, me);
                damage = damage_power(me, "cuff");
                damage+= query("jiali", me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
                                           HIR "$n" HIR "登時便被套得跌跌撞撞，身"
                                           "不由主的立足不穩，猶如中酒昏迷。\n"
                                           NOR);
                me->start_busy(2);
                if (ap / 2 + random(ap) > dp && ! target->is_busy())
                        target->start_busy(3 + ap / 80);
        } else
        {
                msg += CYN "可是$p" CYN "的看破了$P" CYN
                       "的企圖，巧妙的拆招，沒露半點破綻"
                       "。\n" NOR;
                addn("neili", -50, me);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
