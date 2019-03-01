// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "打字訣"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int lvl;

        weapon=query_temp("weapon", me);

        if (! target)
                return notify_fail("你要打哪條蛇？\n");

        if (! target->is_snake())
                return notify_fail("看清楚些，那不是蛇，你瞎打什麼？\n");

        if (! living(target))
                return notify_fail("那條蛇暫時不會動彈了，你不必再打了。\n");

        if ((int)me->query_skill("shedu-qiqiao", 1) < 20)
                return notify_fail("你的蛇毒奇巧還不夠嫻熟，不能打蛇。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的內功的修為不夠，不能打蛇。\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在的內力不夠了。\n");

        if (weapon)
                msg = HIC "\n$N" HIC "舞動手中的" + weapon->name() +
                      HIC "，朝著" + target->name() + HIC "的七寸打"
                      "了過去。\n" NOR;
        else
                msg = HIC "\n$N" HIC "伸出雙指，出指如風，迅躋無比的"
                      "朝著" + target->name() + HIC "的七寸點了過去"
                      "。\n" NOR;

        lvl = (int) me->query_skill("shedu-qiqiao", 1) +
              (int) me->query_skill("dodge");
        lvl = lvl * lvl / 10 * lvl;

        if( lvl/2+random(lvl)<query("combat_exp", target) )
        {
                msg += HIY "結果只聽“啪”的一聲，正打在" + target->name() +
                       HIY "的七寸上。\n" NOR;
                lvl = (int) me->query_skill("force");
                lvl = lvl * 13 / 10;
                lvl = lvl * lvl / 10 * lvl;
//                if ( lvl / 2 + random(lvl) > (int) target->query("combat_exp") )
                if( lvl/2+random(lvl)<query("combat_exp", target) )
                {
                        msg += HIM "只見" + target->name() + HIM
                               "身子輕輕晃動幾下，就不再動彈了。\n" NOR;
                        message_combatd(msg, me);
                        target->unconcious(me);
                } else
                {
                        msg += HIR + "哪裡想到" + target->name() +
                               HIR "挨了這一擊，竟然若無其事，頓時一個翻"
                               "身，直撲向$N" HIR "！\n\n" NOR;
                        message_combatd(msg, me);
                        target->kill_ob(me);
                }
        } else
        {
                msg += WHT "然而" + target->name() + WHT "身子一閃，躲了過去。\n\n" NOR;
                message_combatd(msg, me);
                target->kill_ob(me);
        }
        addn("neili", -50, me);
        me->start_busy(2);

        return 1;
}