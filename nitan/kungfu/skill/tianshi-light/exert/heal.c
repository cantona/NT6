// heal.c
#include <ansi.h>
int exert(object me, object target)
{
    if ( !wizardp(me)) return 0 ;
    write( HIY "你全身放鬆，坐下來開始運功療傷。\n" NOR);
    message("vision",
        HIY + me->name() + "吐出一口金燦燦的血，臉色立刻恢復了正常。\n" NOR,
        environment(me), me);
    set("eff_qi",query("max_qi",  me), me);
    set("qi",query("max_qi",  me), me);
    set("eff_jing",query("max_jing",  me), me);
    set("jing",query("max_jing",  me), me);
    set("neili",query("max_neili",  me), me);
    set("jingli",query("max_jingli",  me), me);
    return 1;
}
