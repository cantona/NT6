// This program is a part of NT MudLIB

#include <ansi.h>
inherit F_CLEAN_UP;

void remove_effect(object me);

int exert(object me, object target)
{
        int skill;

        if( !query("reborn/times", me) )
                return notify_fail("你尚未轉世重生，無法使用寒魔玄力！\n");

        if( target != me )
                return notify_fail("你只能用冰蠶寒功來激發寒魔玄力。\n");

        if( (skill = me->query_skill("freezing-force", 1)) < 1500 )
                return notify_fail("你的冰蠶寒功修為不夠，無法使用寒魔玄力！\n");

        if( me->query_skill("huagong-dafa", 1) < 1500 )
                return notify_fail("你的化功大法修為不夠，無法使用寒魔玄力！\n");

        if( me->query_skill("poison", 1) < 1500 )
                return notify_fail("你對基本毒功的參悟還不夠，無法使用寒魔玄力！\n");

        if( me->query_skill("force", 1) < 1500 )
                return notify_fail("你對基本內功的修為還不夠，無法使用寒魔玄力！\n");

        if( query_temp("freezing", me) )
                return notify_fail("你已經在運起寒魔玄力了。\n");

        if( query("jingli", me)<2000 )
                return notify_fail("你的真氣不夠。\n");

        if( query("neili", me)<5000 )
                return notify_fail("你的內力不夠。\n");

        addn("neili", -1000, me);
        me->receive_damage("qi", 0);

        message_combatd(HIB "$N" HIB "神色凝重，深吸一口氣，體表瞬間變為靛藍色，$N" HIB "隨之擺出各種奇特的造型舞動著。\n"
                       "隨著那些詭異的舞姿，藍色煙氣四起，在空中竟似顯現無數異樣蠶蟲，在$N身周繞行不止，\n"
                       "四周溫度驟降，只剎那間功夫，空氣似乎都凝結了。這瞬間，$N" HIB "如同毒神附體，使人周身顫栗。\n" NOR, me);

        addn_temp("apply/unarmed_damage", 9000, me);
        addn_temp("apply/avoid_freeze", 90, me);
        addn_temp("apply/add_freeze", 90, me);
        addn_temp("apply/add_poison", 90, me);
        set_temp("freezing", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), skill/10);

        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}

void remove_effect(object me)
{
        if( query_temp("freezing", me)){
                addn_temp("apply/add_freeze", -90, me);
                addn_temp("apply/add_poison", -90, me);
                addn_temp("apply/unarmed_damage", -9000, me);
                addn_temp("apply/avoid_freeze", -90, me);
                delete_temp("freezing", me);
                tell_object(me, HIB "$N" HIB "身形一滯，略顯蹣跚，將冰蠶寒魔玄力收回丹田，"
                                "隨著真氣凝成的蠶蟲納入體內，\n$N" HIB"的體色恢復正常，周圍的寒氣也慢慢散開了。\n" NOR);
        }
}
