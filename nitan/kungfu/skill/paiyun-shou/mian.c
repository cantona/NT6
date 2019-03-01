// This program is a part of NITAN MudLIB
// mian 綿綿不絕


#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "綿綿不絕"; }

int perform(object me, object target)
{
        string msg,x;
        int i,j,k,y;

        if( !target ) target = offensive_target(me);
        if( !target || !me->is_fighting(target) )
                return notify_fail("「綿綿不絕」只能在戰鬥中對對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("使用「綿綿不絕」時必須空手！\n");

        if( (int)me->query_skill("paiyun-shou", 1) < 120 )
                return notify_fail("你的排雲推手不夠嫻熟，不會使用「綿綿不絕」。\n");

        if( query("max_neili", me)<1100 )
                return notify_fail("你現在內力修為不夠，不能使用「綿綿不絕」。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在內力太弱，不能使用「綿綿不絕」。\n");

        if( me->query_skill_prepared("hand") != "paiyun-shou"
        ||  me->query_skill_mapped("hand") != "paiyun-shou")
                return notify_fail("你必須全面運用排雲推手，才能使用「綿綿不絕」。\n");


        i = (me->query_skill("paiyun-shou", 1)/2);
        if( target->is_busy() ) i*=2;
        if( (int)me->query_skill("paiyun-shou", 1) > 400 )
        {
                y = 10;
        } else
        if( (int)me->query_skill("paiyun-shou", 1) > 180 )
        {
                y = 8;
        }
        else
        {
                y = 6;
        }
        msg = HIY "$N忽然身隨掌起，雙掌圈動，似虛而實，似柔而剛。一掌拍出，第二掌接踵而至，一連"+chinese_number(y)+"掌，其意如排雲滾滾。\n" NOR;
        message_combatd(msg, me, target);
        addn_temp("apply/attack", i, me);

        for(k = 0; k < y; k++)
        {
                COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);
        }
        addn_temp("apply/attack", -i, me);
        addn("neili", -400, me);
        me->start_busy(2);
        return 1;
}
