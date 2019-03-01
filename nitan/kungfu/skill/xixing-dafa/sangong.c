// sangong.c

#include <ansi.h>

inherit F_SSERVER;

int exert(object me, object target)
{
        if( query("max_neili", me)<1 )
                return notify_fail("你已經將內力散盡，沒什麼必要再散功了。\n");

        tell_object(target, HIY "你默默的按照吸星大法的訣竅將內力散入奇經八脈。\n" NOR);
        message("vision", HIY + me->name() + "呼吸沉重，卻又不像受傷的樣"
                          "子，不知道在修煉什麼厲害的功夫。\n" NOR,
                environment(me), ({ me }));

        me->start_busy(1);
        addn("max_neili", -100, me);
        if( query("max_neili", me)<0 )
                set("max_neili", 0, me);

        return 1;
}

void del_sucked(object me)
{
        delete_temp("sucked", me);
}