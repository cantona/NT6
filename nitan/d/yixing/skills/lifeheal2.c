// /d/yixing/skills/lifeheal2.c
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>

int exert(object me, object target)
{
        if( query("eff_qi", target)*5>query("max_qi", target)*4 )
                return notify_fail("no need now.\n");
        if( userp(me) ) return notify_fail("only used by lamas.\n");
        if( !target ) return notify_fail("你要用真氣為誰療傷？\n");
        if( !living(target) )
                return notify_fail("太遲了，你要治療的人已經死了！\n");

        if( me->is_busy() ) return notify_fail("you are busy now\n");
        if( query("neili", me)<150 )
                return notify_fail("你的真氣不夠。\n");
        if( query("eff_qi", target)<query("max_qi", target)/5 )
                return notify_fail( target->name() + "已經受傷過重，經受不起你的真氣震盪！\n");
        COMMAND_DIR"std/halt"->main(me);

        message_vision(
                HIY "$N運起內功，手掌按在$n後心命門，將真氣輸入$n體內....\n"
                "不久，$N渾身大汗淋漓，顯得十分疲倦。\n"
                "只見$n吐出一口瘀血，臉色看起來紅潤多了。\n" NOR, me, target );

        target->receive_curing("qi", 200 + random(200));
        target->receive_heal("qi", 200 + random(200));

        addn("neili", -50, me);
        addn("qi", -50, me);
        me->start_busy(1);

        return 1;
}