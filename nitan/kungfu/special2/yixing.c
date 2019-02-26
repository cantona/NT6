

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

string name() { return HIW "移形換位" NOR; }

int perform(object me, string skill)
{
        int heal;
        int ap, dp;
        object target;

        if (me->query("jing") < 100)
                return notify_fail("你的精神不濟，難以施展移形換位。\n");

        me->clean_up_enemy();
        target = me->select_opponent();

        if (! me->is_fighting())
                return notify_fail("你又不是在打架，沒事自言自語幹什麼？\n");

        message_vision(HIM "$N" HIM "情急生智，對着$n" HIM
                       "滔滔不絕，亂吹一通，當真是天花亂墜……遲疑間，你已施展出鬼魅般的身法逃之夭夭。\n",
                       me, target);

        me->receive_damage("jing", 30 + random(20));

        message_vision(HIM "$n" HIM "聽得暈暈乎乎，似假非假，若有若無，不知所以，"
                           "手只是緩了一緩，$N" HIM "早已經溜走。\n" NOR,
                            me, target);
        me->set_temp("success_flee", HIG "你成功的逃走了！\n" NOR);
        GO_CMD->do_flee(me);

        return 1;
}
