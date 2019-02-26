
#include <ansi.h>

//inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIY "笑談天下" NOR; }

int perform(object me, string skill, string arg)
{
        int joblv;
        object *t;
        object tob;
        int dex, dodge;

        joblv = me->query_joblv();

        t = me->query_team(); // 必須要組隊才能施展

        if (me->query_temp("special2/tianxia"))
                return notify_fail("「笑談天下」的功效還未消失，無法施展。\n");

        if (me->query("yhjob/job") != "隱士")
                return notify_fail("你的職業錯誤，無法施展。\n");
                
        if (me->query("neili") < 1000)
                return notify_fail("你的內力不足，無法施展。\n");

        if (joblv < 30)
                return notify_fail("你的職業等級不足，無法施展。\n");                

        if (! arrayp(t))
                return notify_fail("該技能只能在組隊的時候施展。\n");
        t -= ({ 0 });
        if (sizeof(t) <= 1)
                return notify_fail("該技能只能在多人組隊的時候施展。\n");
                        
        if (me->is_busy())return notify_fail("等你忙完再説吧！\n");

        message_vision(HIR "$N" HIR "面帶微笑，忽然手臂一揮，狂風大起 …………。\n" NOR, me);

        foreach (tob in t)
        {
                if (1)
                {                        
                        tell_object(tob, HIW + me->name() + "施展出絕招「笑談天下」，提高所有隊友的迴避及有"
                                         "效輕功等級。\n" NOR);
                        dex = 10 + me->query_joblv() * 4 + me->query("lhpoint/special/tianxia") * 20;
                        dodge = 20 + me->query_joblv() + me->query("lhpoint/special/tianxia") * 10;

                               // 不能重複施展
                        if (! tob->query_temp("special2/tianxia"))
                        {
                                tob->set_temp("special2/tianxia", 1);
                                tob->add_temp("dex", dex);
                                tob->add_temp("apply/dodge", dodge);
                                tob->start_call_out( (: call_other, __FILE__, "remove_effect", tob, dex, dodge :), 
                                                   60 + joblv * 10);
                        }
                }
        }
 
        me->add("neili", -1000);
        me->start_busy(1);

        return 1;
}

void remove_effect(object me, int dex, int dodge)
{
        if (! objectp(me))return;
        
        if ((int)me->query_temp("special2/tianxia"))
        {
                me->add_temp("dex", -1 * dex);
                me->add_temp("apply/dodge", -1 * dodge);
                me->delete_temp("special2/tianxia");
                tell_object(me, "「笑談天下」的功效已經消失。\n");
        }
}

