// lifeheal.c
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>

int exert(object me, object target)
{
        if( !wizardp (me)) return 0;
        if( !target )
                return notify_fail("你要用真氣為誰療傷？\n");

        message_combatd( HIY "$N坐了下來運起內功，將手掌貼在$n背心，緩緩地將真氣輸入$n體內....\n\n過了不久，$N額頭上冒出豆大的汗珠，$n吐出一口瘀血，臉色看起來紅潤多了。\n" NOR, me, target );

        set("eff_qi",query("max_qi",  target), target);
        set("qi",query("max_qi",  target), target);

        return 1;
}