// This program is a part of NITAN MudLIB
// huaxue.c

#include <ansi.h>

#define HUAXUE "「" HIR "神刀化血" NOR "」"

inherit F_SSERVER;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        object weapon;
        string msg;
        int skill;

        if( query_temp("huaxue", me) )
                return notify_fail(HIG "你已經運起" + HUAXUE + HIG "了。\n");

        /*
        if (! me->is_fighting())
                return notify_fail(HUAXUE + "只能在戰鬥中使用。\n");
        */

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠！\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的蚩尤狂戰決修為不夠，不能使用" + HUAXUE + "！\n");

        weapon=query_temp("weapon", me);

        if( !objectp(weapon) || query("skill_type", weapon) != "blade" )
                return notify_fail("你沒有裝備刀，難以施展" + HUAXUE + "。\n");

        msg = HIR "$N" HIR "凝神閉目，右手持刀，左手順著" + weapon->name() +
              HIR "刀刃一抹，鮮血頓時將" + weapon->name() + HIR "染紅。\n待到$N"
              HIR "雙目睜開，頓時殺氣沖天！\n" NOR;

        skill = (int)me->query_skill("moshen-xinfa", 1);

        addn("neili", -150, me);
        addn_temp("apply/damage", skill*5, me);
        addn_temp("apply/unarmed_damage", skill*5, me);
        addn_temp("apply/blade", skill, me);
        set_temp("huaxue", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                           me, skill :), skill);

        message_combatd(msg, me);
        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("huaxue", me) )
        {
                addn_temp("apply/damage", -amount*5, me);
                addn_temp("apply/unarmed_damage", -amount*5, me);
                addn_temp("apply/blade", -amount, me);
                delete_temp("huaxue", me);
                tell_object(me, "你的" + HUAXUE + "運行完畢，將內力收回丹田。\n");
        }
}