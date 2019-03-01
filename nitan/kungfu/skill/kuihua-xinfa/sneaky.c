// kuihua-xinfa (protect)
#include <ansi.h>
void remove_effect(object me, int amount);
int exert(object me, object target)
{
    int skill;
    if( target != me ) 
        return notify_fail("葵花心法只能對自己使用。\n");
    if( query("neili", me)<1000 )
        return notify_fail("你的內力不夠。\n");
    if( query_temp("apply/shade_vision", me) )
        return notify_fail("你已經在運功中了。\n");
    skill = me->query_skill("kuihua-xinfa",1);
        if (skill<90) return notify_fail("你的葵花心法還不夠嫻熟。\n");
    message_vision( HIW "$N微一凝神，運起葵花心法，整個人如同被煙霧籠罩一般，漂忽不定。\n"
    "鬼魅至極。\n" NOR, me);
    addn("neili", -300, me);
    set_temp("apply/shade_vision", 1, me);
me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill :), skill/200);
if ((int)me->query_skill("kuihua-xinfa", 1)<450)
    me->improve_skill("kuihua-xinfa", random(me->query_skill("kuihua-xinfa", 1)/10),0);
    if( me->is_fighting() ) me->start_busy(1);
    return 1;
}
void remove_effect(object me, int amount)
{
    if (!me)    return;
    delete_temp("apply/shade_vision", me);
    message_vision( BOLD "$N的葵花心法運行完畢，全身忽的一頓，現出整個身形。\n" NOR, me);
}
void reset() { }
int clean_up() { return 1; }


