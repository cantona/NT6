// Written by Lonely@nitan.org
// 鳳凰涅磐 轉世技能

#include <ansi.h>
inherit F_CLEAN_UP;

void remove_effect(object me);

int exert(object me, object target)
{
        int skill;

        /*
        if( userp(me) && !query("can_exert/linji-zhuang/niepan", me) ) 
                return notify_fail("你未得高人指點，不知該如何施展鳳凰涅磐。\n");  

        if( query("family/family_name", me) != "峨嵋派" )
                return notify_fail("你不是少林弟子，無法使用鳳凰涅磐。\n");
        */

        if( !query("reborn/times", me) )
                return notify_fail("你尚未轉世重生，無法使用鳳凰涅磐！\n");

        skill = me->query_skill("linji-zhuang", 1);
        if( skill < 1000 )
                return notify_fail("你的臨濟十二莊修為還不夠，無法使用鳳凰涅磐！\n");

        if( query("jingli", me)<1000 )
                return notify_fail("你的真氣不夠。\n");

        if( query("neili", me)<2000 )
                return notify_fail("你的內力不夠。\n");

        if( objectp(target) && target != me ) {
                if( !target->query_weak() )
                        return notify_fail(target->name() + "並沒有處於虛弱狀態。\n");

                addn("neili", -1000, me);
                me->receive_damage("qi", 0);
                target->clear_weak();
                message_combatd(HIY "只見$N" HIY "屏息靜氣，雙掌貼在"+target->name()+"背後，交錯運行大小二莊，只見"+target->name()+"全身被紫芒籠罩。\n" NOR, me);
                tell_object(target, HIG"\n你感覺身體狀態慢慢的復原了。。。\n\n" NOR);
                tell_object(me, HIG"\n你替"+target->name()+"消除了虛弱狀態。。。\n\n" NOR);
                if( me->is_fighting() ) me->start_busy(3);
                return 1;
        }

        if( query_temp("niepan", me) )
                return notify_fail("你已經在運起鳳凰涅磐了。\n");

        addn("neili", -1000, me);
        me->receive_damage("qi", 0);

        message_combatd(HIY "$N" HIY "神色忽而歡歎、忽而憂心、轉瞬間又化做不喜不悲之狀，\n隨著$N" HIY "張開眼神，一屢精光乍現及逝，$N"HIY"的氣習卻已全然不同。\n" NOR, me);

        addn_temp("apply/avoid_busy", 100, me);
        addn_temp("apply/avoid_weak", 100, me);
        addn_temp("apply/reduce_damage", 70, me);
        set_temp("niepan", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), skill/2);

        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}

void remove_effect(object me)
{
        if( query_temp("niepan", me)){
                addn_temp("apply/avoid_busy", -100, me);
                addn_temp("apply/avoid_weak", -100, me);
                addn_temp("apply/reduce_damage", -70, me);
                delete_temp("niepan", me);
                tell_object(me, "你的臨濟莊運行完畢，將內力收回丹田。\n");
        }
}
