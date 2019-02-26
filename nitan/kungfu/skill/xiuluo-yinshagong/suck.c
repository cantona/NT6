#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;
 
int exert(object me, object target)
{
        mapping p;
        string msg;
        object ob;
        int amount;
        int exp;
        int lvl;
        int sk;

        if (! target || target == me)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target)
                return notify_fail("你要取哪隻蟲的毒液練藥？\n");

        if (! target->is_worm())
                return notify_fail("看清楚些，那可不是毒蟲。\n");

        if (living(target))
                return notify_fail("那隻蟲還精神着呢，你找死啊。\n");

        if ((int)me->query_skill("wudu-qishu", 1) < 100)
                return notify_fail("你的五毒奇術不夠嫻熟，不能煉製毒藥。\n");

        if ((int)me->query_skill("xiuluo-yinshagong", 1) < 100)
                return notify_fail("你修羅陰煞功修為不夠，不能煉製毒藥。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在內力不足，難以煉製毒藥。\n");

        addn("neili", -50, me);
        me->start_busy(random(3));

        msg = HIR "\n$N" HIR "伸出食指，點在" + target->name() +
              HIR "腹部，默運內力迫出毒液練藥。\n" NOR;

        p=query("worm_poison", target);
        if (! mapp(p))
                return notify_fail("看來你是弄不出什麼毒液來了。\n" NOR);

        lvl = (int)me->query_skill("poison", 1) / 3 +
              (int)me->query_skill("wudu-qishu", 1) / 3 +
              (int)me->query_skill("xiuluo-yinshagong", 1) / 3;

        amount = p["level"] * p["remain"];
        if (amount > lvl)
                amount = lvl;
        
        p["remain"] = (p["level"] * p["remain"] - amount) /
                       p["level"];
        target->apply_condition("poison-supply", 1);

        if (! amount)
        {
                msg += WHT "$N" WHT "擠了半天，結果啥也沒有擠出來，算是"
                       "白忙活了。\n\n" NOR;
                message_vision(msg, me);
                return 1;
        }

        if (amount < lvl)
        {
                msg += WHT "$N" WHT "擠了一點毒液出來。\n" NOR;
                message_vision(msg, me);
                tell_object(me, HIY "可惜這點毒液連煉一顆毒藥都不夠。\n\n" NOR);
                return 1;
        }

        msg += HIW "$N" HIW "將" + target->name() + HIW "的毒液逼出，在"
               "內力的作用下化成了一顆晶瑩剔透的藥丸。\n" NOR;
        message_vision(msg, me);
        tell_object(me, HIC "你煉製了一顆蟲毒藥丸。\n\n" NOR);

        exp = lvl / 4;
        me->improve_skill("poison", 2 + random(exp));
        if (me->can_improve_skill("wudu-qishu"))
                me->improve_skill("wudu-qishu", 2 + random(exp / 2));

        if (me->can_improve_skill("xiuluo-yinshagong"))
                me->improve_skill("xiuluo-yinshagong", 2 + random(exp / 3), 1);

        ob = new("/clone/misc/chongdu");
        ob->set("poison",([
                "level" : lvl,
                "id":query("id", me),
                "name"  : "蟲毒",
                "duration" : 10,
        ]));
        ob->move(me, 1);

        return 1;
}
