// This program is a part of NT MudLIB
// 佛光普照 轉世技能
// buddha.c

#include <ansi.h>
inherit F_CLEAN_UP;

void remove_effect(object me);

int exert(object me, object target)
{
        int skill;

        if( userp(me) && !query("can_exert/yijinjing/buddha", me) ) 
                return notify_fail("你未得高人指點，不知該如何施展佛光普照。\n");  
        /*
        if( query("family/family_name", me) != "少林派" )
                return notify_fail("你不是少林弟子，無法使用佛光普照。\n");
        */

        if( !query("reborn/times", me) )
                return notify_fail("你尚未轉世重生，無法使用佛光普照！\n");

        if( target != me )
                return notify_fail("你只能用易筋經來激發佛光普照。\n");

        if( (skill = me->query_skill("yijinjing", 1)) < 1000 )
                return notify_fail("你的易筋經神功沒有學成，無法使用佛光普照！\n");

        if( me->query_skill("jingang-buhuaiti", 1) < 1000 )
                return notify_fail("你的金剛不壞體神功修為不夠，無法使用佛光普照！\n");

        if( me->query_skill("buddhism", 1) < 1000 )
                return notify_fail("你對禪宗心法的參悟還不夠，無法使用佛光普照！\n");

        if( me->query_skill_mapped("parry") != "jingang-buhuaiti" )
                return notify_fail("你必須激發金剛不壞體，才能使用佛光普照！\n");

        if( query_temp("buddha", me) )
                return notify_fail("你已經在運起佛光普照了。\n");

        if( query("jingli", me)<2000 )
                return notify_fail("你的真氣不夠。\n");

        if( query("neili", me)<5000 )
                return notify_fail("你的內力不夠。\n");

        addn("neili", -1000, me);
        me->receive_damage("qi", 0);

        message_combatd(HIY "只聽$N" HIY "高呼佛號，運起佛光普照，霎那間全身竟猶如鍍金一般，發出燦燦金光。\n" NOR, me);

        addn_temp("apply/avoid_busy", 90, me);
        addn_temp("apply/avoid_weak", 90, me);
        addn_temp("apply/reduce_damage", 90, me);
        set_temp("buddha", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), skill/10);

        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}

void remove_effect(object me)
{
        if( query_temp("buddha", me)){
                addn_temp("apply/avoid_busy", -90, me);
                addn_temp("apply/avoid_weak", -90, me);
                addn_temp("apply/reduce_damage", -90, me);
                delete_temp("buddha", me);
                tell_object(me, "你運行完畢，將內力收回丹田，佛光消失。\n");
        }
}
