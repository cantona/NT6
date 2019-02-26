//Cracked by Roath
// zhao.c for ding-force
// 金鐘罩

#include <ansi.h>

int exert(object me, object target)
{
        int lv, dur, drop;
        string str;
        object ob;

        if( !me->is_fighting() )
                return notify_fail("等跟人打架時再用吧！\n");
        if( query_temp("huti", me) )
                return notify_fail("你已經運起金鐘罩護體功了。\n");

        lv = (int)me->query_skill("ding-force", 1);
        dur=query("neili", me);

        if (lv > 150)
        {
                drop = 200 * 150 / lv;
                dur = (dur - drop)/drop;
                str = HIR + me->name() + "騎馬蹲襠，氣存丹田，暴喝一聲：來！\n"
                + HIG + "一道金光飛來，半空中突然落下一隻黃金大鐘把" +
                me->name() + "罩在裏面。\n" + NOR;
        }
        if (dur < 1)
                return notify_fail("你的內力不夠運用金鐘罩。\n");

        seteuid(geteuid(me));
        /*
        ob =new("/u/ding/zhao.c");
        ob->move(me);
        ob->wear(me);
        */
       
        addn("neili", -drop, me);
        me->apply_condition("zhao", dur);
        set_temp("huti", 1, me);
        write(HIG + "你運起金鐘罩護體功。\n" + NOR);
        message("vision", str, environment(me), me);
        return 1;
}
