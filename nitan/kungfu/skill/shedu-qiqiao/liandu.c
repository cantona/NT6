// liandu.c 毒液練藥

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "煉毒"; }

int perform(object me, object target)
{
        mapping p;
        string msg;
        object ob;
        int amount;
        int exp;
        int lvl;
        int sk;

        if (! target)
                return notify_fail("你要取哪條蛇的毒液練藥？\n");

        if (! target->is_snake())
                return notify_fail("看清楚些，那不是蛇，你瞎搞什麼？\n");

        if (living(target))
                return notify_fail("那條蛇還精神著呢，你找死啊。\n");

        if ((int)me->query_skill("shedu-qiqiao", 1) < 80)
                return notify_fail("你的蛇毒奇巧還不夠嫻熟，不能煉制毒藥。\n");

        if ((int)me->query_skill("hamagong", 1) < 80)
                return notify_fail("你的蛤蟆功的修為不夠，不能煉制毒藥。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的內力不夠！\n");

        addn("neili", -50, me);
        me->start_busy(random(3));

        msg = HIC "\n$N" HIC "伸出雙指，捏住" + target->name() +
              HIC "的嘴巴，以內力迫出毒液練藥。\n" NOR;

        p=query("snake_poison", target);
        if (! mapp(p))
                return notify_fail("看來你是弄不出什麼毒液來了。\n" NOR);

        lvl = (int) me->query_skill("poison", 1) / 2 +
              (int) me->query_skill("shedu-qiqiao", 1);

        if (! undefinedp(p["level"])) p["level"] = 1;
        amount = p["level"] * p["remain"];
        if (amount > lvl)
                amount = lvl;

        p["remain"] = (p["level"] * p["remain"] - amount) /
                       p["level"];
        target->apply_condition("poison-supply", 1);

        if (! amount)
        {
                msg += WHT "$N" WHT "擠了半天，結果啥也沒有擠出來，算是白忙活了。\n\n" NOR;
                message_combatd(msg, me);
                return 1;
        }

        if (amount < lvl)
        {
                msg += WHT "$N" WHT "擠了一點毒液出來。\n\n" NOR;
                message_combatd(msg, me);
                tell_object(me, HIY "可惜這點毒液連練一顆毒藥都不夠。\n" NOR);
                return 1;
        }

        msg += HIM "$N" HIM "將" + target->name() + HIM "的毒液悉數擠"
               "出，在內力的作用下化成了一顆晶瑩剔透的藥丸。\n\n" NOR;
        message_combatd(msg, me);
        tell_object(me, HIC "你煉制了一顆蛇毒藥丸。\n" NOR);

        // improve skill
        exp = lvl / 5;
        me->improve_skill("poison", 2 + random(exp));
        if (me->can_improve_skill("shedu-qiqiao"))
                me->improve_skill("shedu-qiqiao", 2 + random(exp));

        if (me->can_improve_skill("hamagong"))
                me->improve_skill("hamagong", 2 + random(exp / 6), 1);

        // create the object
        ob = new("/clone/misc/shedu");
        ob->set("poison",([
                "level" : lvl,
                "id":query("id", me),
                "name"  : "蛇毒",
                "duration" : 10,
        ]));
        ob->move(me);

        return 1;
}