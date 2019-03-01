
#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIG "舍我其誰" NOR; }

int perform(object me, string skill, string arg)
{
        int joblv;
		object *t;
		object tob;
		int qi, jing;

		joblv = me->query_joblv();

		t = me->query_team(); // 必須要組隊才能施展

        if (time() - me->query_temp("special2/shewo/lasttime") < 60)
                return notify_fail("該技能在一分鐘內只能施展一次。\n");

		if (me->query("yhjob/job") != "俠客")
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
			
        if (me->is_busy())return notify_fail("等你忙完再說吧！\n");

        message_vision(HIC "$N" HIC "雙目微閉，頓時全身上下被一道金光籠罩，慢慢地，金光擴散開來 …………\n" NOR, me);

		foreach (tob in t)
		{
			if (! objectp(tob))continue;

			if (1)
			{			
				tell_object(tob, HIW + me->name() + "施展出絕招「舍我其誰」，恢復所有隊友的精力及氣血。\n" NOR);
				qi = 500 + me->query_joblv() * 50 + me->query("lhpoint/special/shewo")* 400;
				jing = 200 + me->query_joblv() * 30 + me->query("lhpoint/special/shewo") * 300;

				// 恢復受傷狀態
				if (tob->query("eff_qi") + qi / 2 > tob->query("max_qi"))
						tob->set("eff_qi",tob->query("max_qi"));
				else
						tob->add("eff_qi", qi / 2);

				// 恢復氣血
				if (tob->query("qi") + qi > tob->query("eff_qi"))
						tob->set("eff_qi", tob->query("eff_qi"));
				else
						tob->add("qi", qi);
				
				// 恢復精力/精氣受傷狀態
				if (tob->query("eff_jing") + jing / 2 > tob->query("max_jing"))
						tob->set("eff_jing", tob->query("max_jing"));
				else
						tob->add("eff_jing", jing / 2);

				if (tob->query("eff_jingli") + jing / 4 > tob->query("max_jingli"))
						tob->set("eff_jingli", tob->query("max_jingli"));
				else
						tob->add("eff_jingli", jing / 4);

				if (tob->query("jing") + jing / 2 > tob->query("eff_jing"))
						tob->set("jing", tob->query("eff_jing"));
				else
						tob->add("jing", jing / 2);

				if (tob->query("jingli") + jing / 2 > tob->query("eff_jingli"))
						tob->set("jingli", tob->query("eff_jingli"));
				else
						tob->add("jingli", jing / 2);
			}
		}
 
		me->set_temp("special2/shewo/lasttime", time());
        me->add("neili", -1000);
        me->start_busy(1);

        return 1;
}
