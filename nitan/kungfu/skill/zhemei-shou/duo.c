// This program is a part of NITAN MudLIB
// duo.c 空手入白刃

#include <ansi.h>

inherit F_SSERVER;

string name() { return "空手入白刃"; }

int perform(object me, object target)
{
        string msg;
        object weapon, weapon2;
        int ap, dp, skill;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        skill = me->query_skill("zhemei-shou", 1);

        if (! me->is_fighting())
                return notify_fail("空手入白刃只能對戰鬥中的對手使用。\n");

        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("你必須空手。\n");

        if( !objectp(weapon2=query_temp("weapon", target)) )
                return notify_fail("對方沒有兵刃，你不用擔心。\n");

        if (skill < 50)
                return notify_fail("你的天山折梅手等級不夠, 不能空手入白刃！\n");

        if ((int)me->query_skill("bahuang-gong", 1) < 50 &&
            (int)me->query_skill("xiaowuxiang", 1) < 80 &&
            (int)me->query_skill("beiming-shengong", 1) < 50)
                return notify_fail(RED"你本門內功火候不夠，使不出「空手奪白刃」。\n"NOR);

        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠，無法空手入白刃！\n");

        msg = CYN "$N凝神閉息，打算施展空手入白刃的絕技. \n";
        message_combatd(msg, me, target);

        ap = attack_power(me, "hand");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -50, me);
                msg = "$N使出空手入白刃的絕招, $n頓時覺得眼前一花，手腕一麻，手中兵刃脱手而出！\n" NOR;
                weapon2->move(me);
                if (weapon2->is_item_make() && random(2))
                {
                        weapon2->move(target);
                        msg += "那可是$n的隨身傢伙！$n手一伸將它奪回來。\n" NOR;
                }
                me->start_busy(2);
        }
        else
        {
                msg = "可是$p的看破了$P的企圖，立刻採取守勢，使$P沒能奪下兵刃。\n"NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);
        return 1;
}