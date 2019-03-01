//lian.c 落霞滿天
// looo/2001/6/24
#include <ansi.h>

#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)

{
        object weapon;
        string msg;

        int i, j, skill;
        skill = (int)(me->query_skill("cuff"));
        j = skill/4;
        i=5+query("tianmo_jieti/times", me);

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))

                return notify_fail("「落霞滿天」只能在戰鬥中對對手使用。\n");

        if(me->query_skill_mapped("cuff") != "luorishenquan-cuff") 
                return notify_fail("你沒有用落日神拳，無法使用「落霞滿天」絕招！\n");

        if (me->query_skill_prepared("cuff") != "luorishenquan-cuff")
                return notify_fail("你沒有準備使用落日神拳，無法施展「落霞滿天」絕招。\n");

        if( objectp(weapon=query_temp("weapon", me)) || 
            objectp(weapon=query_temp("handing", me)) )
                return notify_fail("你必須空著雙手才能使用拳法絕招。\n");

        if( (int)me->query_skill("luorishenquan-cuff", 1) < 220 )
                return notify_fail("你的落日神拳法還不夠嫻熟，使不出「落霞滿天」絕技。\n");

        if( (int)me->query_skill("force") < 300 )
                return notify_fail("你的內功等級還不夠，使不出「落霞滿天」絕技。\n");

        if( query("max_neili", me)<(me->query_skill("force")+i*j+2000) )
                return notify_fail("你的內力修為需要進一步提高，才能使出「落霞滿天」這種超強絕招。\n");

        if( query("neili", me)<(me->query_skill("force")+i*j) )
                return notify_fail("你現在真氣太弱，還敢使用「落霞滿天」？\n");


        msg = HIM "\n$N" HIM "身形飄飛，雙拳急驟擊出，四周全是飛舞的拳影，赫然正是『落霞滿天』！\n" NOR;

        message_combatd(msg, me, target);

        addn_temp("apply/str", 7, me);
        addn_temp("apply/damage", j, me);
        addn_temp("apply/attack", j, me);

        while (i-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->start_busy(4);

        target->start_busy(1);

        addn_temp("apply/str", -7, me);
        addn_temp("apply/damage", -j, me);
        addn_temp("apply/attack", -j, me);

        return 1;
}
