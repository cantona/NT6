
#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIR "號令八方" NOR; }

int perform(object me, string skill, string arg)
{
        int joblv;
	object *t;
	object tob;
	int attack, damage;

	joblv = me->query_joblv();

	t = me->query_team(); // 必須要組隊才能施展

        if (me->query_temp("special2/haoling"))
                return notify_fail("「號令八方」的功效還未消失，無法施展。\n");

	if (me->query("yhjob/job") != "魔師")
		return notify_fail("你的職業錯誤，無法施展。\n");
		
	if (me->query("neili") < 1200)
		return notify_fail("你的內力不足，無法施展。\n");

	if (joblv < 30)
		return notify_fail("你的職業等級不足，無法施展。\n");		

	if (! arrayp(t))
		return notify_fail("該技能只能在組隊的時候施展。\n");

        t -= ({ 0 });
	if (sizeof(t) <= 1)
		return notify_fail("該技能只能在多人組隊的時候施展。\n");
			
        if (me->is_busy())return notify_fail("等你忙完再說吧！\n");

        message_vision(HIR "$N" HIR "雙目發光，振臂高呼，“魔由心生，號令八方！” ，聲音激盪四周，令人生畏。\n" NOR, me);

	foreach (tob in t)
	{
		if (1)
		{			
			tell_object(tob, HIW + me->name() + "施展出絕招「號令八方」，提高所有隊友的命中及傷害力。\n" NOR);
			attack = 100 + me->query_joblv() * 20 + me->query("lhpoint/special/haoling") * 60;
			damage = 100 + me->query_joblv() * 30 + me->query("lhpoint/special/haoling") * 80;

              	        // 不能重復施展
			if (! tob->query_temp("special2/haoling"))
			{
				tob->set_temp("special2/haoling", joblv);
				tob->add_temp("apply/attack", attack);
				tob->add_temp("apply/damage", damage);
				tob->add_temp("apply/unarmed_damage", damage);
				tob->start_call_out( (: call_other, __FILE__, "remove_effect", tob, attack, damage :), 
				                    60 + joblv * 10);
			}
		}
	}
 
        me->add("neili", -1200);
        me->start_busy(1);

        return 1;
}

void remove_effect(object me, int attack, int damage)
{
        if ((int)me->query_temp("special2/haoling"))
        {
		me->add_temp("apply/attack", -1 * attack);
		me->add_temp("apply/damage", -1 * damage);
		me->add_temp("apply/unarmed_damage", -1 * damage);
	        me->delete_temp("special2/haoling");
	        tell_object(me, "「號令八方」的功效已經消失。\n");
        }
}

