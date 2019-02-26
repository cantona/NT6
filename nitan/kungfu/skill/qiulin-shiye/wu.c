#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "隨風而舞"; }

int perform(object me, object target)
{
        string msg;
        object env = environment(me);
        mapping*obb=query("exits", env);

        if (! target) target = offensive_target(me);

        if (! target || ! target->is_character() ||
            ! me->is_fighting(target))
                return notify_fail("你只能在戰鬥中使用「隨風而舞」。\n");

        if ((int)me->query_skill("qiulin-shiye", 1) <  90)
                return notify_fail("你目前功力還使不出「隨風而舞」。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的內力不夠。\n");

        if (me->is_busy())
                return notify_fail("你現在正忙着呢。\n");

        addn("neili", -200, me);
        msg = HIC"$N突然輕噓一聲，身形一展，向隨風飄舞而上，身形越來越小。\n"NOR;
        me->start_busy(1);

        if( random(query("combat_exp", me)/100)>
            query("combat_exp", target)/400 )
        {
                if (! target->is_busy())
                target->start_busy(4 + random(4));
                me->receive_damage("qi", 200);
                me->receive_damage("jing",80);
                if (sizeof(obb) > 0) me->move(obb[0]);
                msg += RED"只見$n只看的目瞪口呆,一時手忙腳亂起來，不知如何是好。\n"NOR;
        } else
        {
                msg += HIC "可是$p卻暴身南而起，大喝一聲：“那裏走！”，攔在你的前面，$P這招沒有得逞。\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}

