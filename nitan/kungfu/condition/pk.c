#include <ansi.h>

int dispel() { return 0; }

int update_condition(object me, int duration)
{
        if (duration < 1)
        {
                tell_object(me, HIR "執法精靈告訴你：“你已被禁閉二"
                                "十四小時，現在你自由了！”\n");
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "聽説" + me->name(1) + HIM + "刑滿釋放了。");
                me->set("combat/WPK", 0);
                me->set("combat/PKS", 0);
                return 0;
        }
        // 計劃中不減少懲罰時間
        if (! me->query("doing"))me->apply_condition("pk", duration - 1);
        return 1;
}
