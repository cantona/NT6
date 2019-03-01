// jixue.c 血海魔功祭血大法

#include <ansi.h>

inherit F_SSERVER;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        object weapon;  
        string msg;
        int skill;

        if( query_temp("jixue", me) )
                return notify_fail(HIG"你已經運起祭血大法了。\n");

        if (! me->is_fighting())
                return notify_fail("「祭血大法」只能在戰鬥中使用。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠！\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的血海魔功的修為不夠，不能使用祭血大法！\n");
        msg = HIR "$N" HIR "使出血海魔功「祭血大法」，剎時間臉色變得"
              "血紅，"HIR "$N" HIR "忽地咬破舌尖，噴出一口鮮血！\n" NOR;

        skill = (int)me->query_skill("xuehai-mogong", 1);

        if( query("qi", me)>query("max_qi", me)*6/10 )
        {       
                addn_temp("apply/damage", skill*20, me);
                addn_temp("apply/unarmed_damage", skill*20, me);
                set_temp("jixue", 1, me);
                me->start_call_out((: call_other, __FILE__, "remove_effect",
                                   me, skill :), skill);
                addn("neili", -150, me);
                me->receive_damage("qi",query("max_qi", me)/2);
        } else
                msg = HIR "$N" HIR "發現自己氣力不濟，沒能提起祭血大法。\n" NOR;

        message_combatd(msg, me);
        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("jixue", me) )
        {
                addn_temp("apply/damage", -amount*20, me);
                addn_temp("apply/unarmed_damage", -amount*20, me);
                delete_temp("jixue", me);
                tell_object(me, "你的祭血大法運行完畢，將內力收回丹田。\n");
        }
}
