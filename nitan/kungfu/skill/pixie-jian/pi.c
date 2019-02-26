#include <ansi.h>
#include <combat.h>

#define PI "「" HIW "羣邪辟易" NOR "」"

inherit F_SSERVER;

string *finger_name = ({ "左手中指", "左手無名指", "左手食指",
                         "右手中指", "右手無名指", "右手食指", }); 

int perform(object me, object target)
{
        string msg;
        string name;
        object weapon;
        int i;
        int skill;
        int count;
        
        /*
        if( userp(me) && !query("can_perform/pixie-jian/pi", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");
        */
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(PI "只能對戰鬥中的對手使用。\n");

        weapon=query_temp("weapon", me);

        if( weapon && query("skill_type", weapon) != "sword" && 
            query("skill_type", weapon) != "pin" )
                return notify_fail("你使用的武器不對，難以施展" PI "。\n");

        if( query_temp("weapon", me) )
                name = "手中" + weapon->name();
        else
                name = finger_name[random(sizeof(finger_name))];

        skill = me->query_skill("pixie-jian", 1);

        if (skill < 120)
                return notify_fail("你的辟邪劍法不夠嫻熟，難以施展" PI "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不足，難以施展" PI "。\n");

        if (weapon && me->query_skill_mapped("sword") != "pixie-jian")
                return notify_fail("你沒有準備使用辟邪劍法，難以施展" PI "。\n");

        if (! weapon && me->query_skill_prepared("unarmed") != "pixie-jian")
                return notify_fail("你沒有準備使用辟邪劍法，難以施展" PI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "$N" HIW "身形忽然變快，驀的衝向$n" HIW "，" + name +
              HIW "幻作數道虛影，頓時無數星光一齊射向$n" HIW "！\n" NOR;
        message_combatd(msg, me, target);

        count = skill / 4;
        addn_temp("apply/attack", count, me);
        addn_temp("apply/damage", count, me);
        addn_temp("apply/unarmed_dage", count, me);

        addn_temp("pixie-jian/hit_msg", 1, me);

        for (i = 0; i < 9; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(3) == 0 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        addn("neili", -100, me);
        me->start_busy(1 + random(7));
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count, me);
        addn_temp("apply/unarmed_dage", -count, me);
        delete_temp("pixie-jian/hit_msg", me);
        return 1;
}
