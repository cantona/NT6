// This program is a part of NITAN MudLIB
// chumo.c 盪妖除魔

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "盪妖除魔"; }

int perform(object me)
{
        string msg;
        object target;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「盪妖除魔」只能在戰鬥中對對手使用。\n");

        skill = me->query_skill("yingzhua-gong", 1);

        if (skill < 135)
                return notify_fail("你的鷹爪功等級不夠，不會使用「盪妖除魔」！\n");

        if( query("neili", me)<250 )
                return notify_fail("你的真氣不夠，無法運用「盪妖除魔」！\n");

        if (me->query_skill_mapped("claw") != "yingzhua-gong")
                return notify_fail("你沒有激發鷹爪功，無法使用「盪妖除魔」！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "微微一笑，雙掌緩緩的向$n" HIY "抓出，此招"
              "看上去也平平無奇，並無多少精妙變化！\n" NOR;

        ap = attack_power(me, "claw") + me->query_skill("force");
        dp = defense_power(target, "dodge") + me->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -200, me);
                damage = damage_power(me, "claw");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55,
                                           HIR "不知怎麼的，$p" HIR "卻偏偏躲不開$P"
                                           HIR "這一抓，結果被抓了個正中，不由得悶"
                                           "哼一聲，退了幾步。\n" NOR);
                me->start_busy(1 + random(2));
        } else
        {
                msg += CYN "可是$p" CYN "沒有輕視$P" CYN
                       "這一抓，連忙招架，順勢躍開，沒有被$P"
                       CYN "得手。\n" NOR;
                addn("neili", -40, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}