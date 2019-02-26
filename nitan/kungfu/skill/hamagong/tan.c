// 彈射毒藥

#include <ansi.h>

inherit F_SSERVER;

int exert(object me, object target)
{
        object du;
        int damage;
        int ap;
        string msg;

        if( query("no_fight", environment(me)) )
                return notify_fail("這裏不能戰鬥，你不可以使用毒技傷人。\n");

        if (! target || me == target)
                return notify_fail("你想攻擊誰？\n");

        if (target->query_competitor())
                return notify_fail("比武的時候最好是正大光明的較量。\n");

        if ((int)me->query_skill("poison", 1) < 80)
                return notify_fail("你的基本毒技火候不夠。\n");

        if ((int)me->query_skill("hamagong", 1) < 100)
                return notify_fail("你的內功火候不夠。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在內力不足，不能彈射毒藥。\n");

        if( !objectp(du=query_temp("handing", me)) )
                return notify_fail("你得先準備(hand)好毒藥再説。\n");

        if( !mapp(query("poison", du)) )
                return notify_fail(du->name() + "又不是毒藥，你亂彈什麼？\n");

        msg = CYN "$N" CYN "運轉內力，輕輕懸起一些" + du->name() +
              CYN "對準$n" CYN "彈了過去。\n" NOR;
        me->start_busy(2 + random(2));
        addn("neili", -300, me);

        if( query("neili", me)/2+random(query("neili", me))<
            query("neili", target) )
        {
                msg += WHT "然而$n輕輕一抖，將$N射過來的" + du->name() +
                       WHT "悉數震開。\n" NOR;
        } else
        {
                ap = me->query_skill("poison", 1) / 2 +
                     me->query_skill("force");
                if (ap / 2 + random(ap) < target->query_skill("dodge") * 3 / 2)
                {
                        msg += WHT "$n見勢不妙，急忙騰挪身形，避開了$N的攻擊。\n" NOR;
                        target->start_busy(1);
                } else
                {
                        msg += GRN "$n連忙躲閃，結果仍然覺得微微一陣痠麻。\n" NOR;
                        target->affect_by(query("poison_type", du),query("poison", du));
                        target->start_busy(1);
                }
        }

        du->add_amount(-1);
        message_combatd(msg, me, target);
        me->want_kill(target);
        if (! target->is_killing(me)) target->kill_ob(me);

        return 1;
}