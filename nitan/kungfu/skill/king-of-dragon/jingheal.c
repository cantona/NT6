// jingheal.c
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>

int exert(object me, object target)
{
        if ( !wizardp(this_player()) )
                return notify_fail("你無權進行精的治療！\n");

        if( !target )
                return notify_fail("你要用真氣為誰療傷？\n");

        message_combatd(
                HIY "$N坐了下來運起內功，將手掌貼在$n背心，緩緩地將真氣輸入$n體內....\n\n"
                "過了不久，$N額頭上冒出豆大的汗珠，$n吐出一口瘀血，臉色看起來紅潤多了。\n" NOR,
                me, target );

        set("eff_jing",query("max_jing",  target), target);
        set("jing",query("max_jing",  target), target);


        return 1;
}