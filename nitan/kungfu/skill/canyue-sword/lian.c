//lian.c 眾星捧月
// looo/2001/6/24
#include <ansi.h>

#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)

{
        object weapon;
        string msg;

        int i, j, skill;
        skill = (int)(me->query_skill("sword"));
        j = skill/4;
        i=5+query("tianmo_jieti/times", me);

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))

                return notify_fail("「眾星捧月」只能在戰鬥中對對手使用。\n");

        if( query("gender", me) != "男性" )
                return notify_fail("你不是堂堂男子,無法使出如此絕技。\n");

        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("你必須使用武器才能使用「眾星捧月」！\n");

        if( query("skill_type", weapon) != "sword" )
                return notify_fail("你沒有用劍，無法使用「眾星捧月」！\n");

        if(me->query_skill_mapped("sword") != "canyue-sword") 
                return notify_fail("你沒有用殘月劍法，無法使用「眾星捧月」！\n");

        if( (int)me->query_skill("canyue-sword", 1) < 220 )
                return notify_fail("你的殘月劍法還不夠嫻熟，使不出「眾星捧月」絕技。\n");

        if( (int)me->query_skill("force") < 300 )
                return notify_fail("你的內功等級還不夠，使不出「眾星捧月」絕技。\n");

        if( query("max_neili", me)<(me->query_skill("force")+i*j+2000) )
                return notify_fail("你的內力修為需要進一步提高，才能使出「眾星捧月」這種超強絕招。\n");

        if( query("neili", me)<(me->query_skill("force")+i*j) )
                return notify_fail("你現在真氣太弱，還敢使用「眾星捧月」？\n");


        msg = HIM "\n$N" HIM "傲然一笑，手中"+ weapon->name() + HIM "挽出一個完美的滿月，周圍點點星光燦爛閃爍，儼然一幅「眾星捧月」的美景。\n"
              HIM "忽然間星圖變幻，萬千星光護着一道朦朧華麗的月光向" HIM "$n" HIM "不斷電射而去。\n" NOR;

        message_combatd(msg, me, target);

        addn_temp("apply/str", 7, me);
        addn_temp("apply/damage", j, me);
        addn_temp("apply/attack", j, me);

        while (i--)
        {
                if (! me->is_fighting(target))
                        break;
                msg = HIB "\n星光萬千，明月獨尊！！\n" NOR;
                message_vision(msg,me,target);
                COMBAT_D->do_attack(me, target, weapon, 0);
                addn("neili", -j, me);
        }

        me->start_busy(4);

        target->start_busy(1);

        addn_temp("apply/str", -7, me);
        addn_temp("apply/damage", -j, me);
        addn_temp("apply/attack", -j, me);

        return 1;
}