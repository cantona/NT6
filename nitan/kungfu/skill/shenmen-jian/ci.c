// This program is a part of NITAN MudLIB

#include <ansi.h>
inherit F_SSERVER;

string name() { return "神門刺"; }

int perform(object me)
{
        string msg;
        object weapon, weapon2, target;
        int skill, ap, dp;

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        skill = me->query_skill("shenmen-jian", 1);

        if( !(me->is_fighting() ))
                return notify_fail("神門刺只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon2=query_temp("weapon", target)) )
                return notify_fail("對方沒有使用兵器，你用了神門刺也沒用。\n");

        if( skill < 160)
                return notify_fail("你的神門十三劍等級不夠, 無法施展神門刺。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的內力不夠，無法施展神門刺！\n");

        msg = HIY "突然$N" HIY "一聲冷哼，手中" +weapon->name()+ NOR + HIY
                  "中攻直進，直刺$n拿著的" +weapon2->name()+ NOR + HIY"的"
                  "手腕。\n" NOR;

        message_combatd(msg, me, target);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if( ap / 2 + random(ap) > dp )
        {
                addn("neili", -120, me);
                msg = HIR "$n只覺手腕一陣刺痛，手中" +weapon2->name()+ NOR + HIR
                      "再也捉拿不住，脫手而飛！\n" NOR;
                me->start_busy(1 + random(2));
                if (! target->is_busy())
                        target->start_busy(2);
                weapon2->move(environment(target));
        }
        else
        {
                addn("neili", -40, me);
                msg = CYN "可是$n看破了$N的企圖，將手中兵刃揮舞得密不透風，擋開了$N" CYN
                      "的兵器。\n"NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}