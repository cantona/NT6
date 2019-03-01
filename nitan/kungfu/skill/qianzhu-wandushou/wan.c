#include <ansi.h>

inherit F_SSERVER;
string name() { return "萬蠱噬天"; }

int perform(object me, object target)
{
        mapping prepare;
        string msg;
        int skill;
        int i;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("「萬蠱噬天」只能對戰鬥中的對手使用。\n");

        if (me->query_skill_prepared("hand") != "qianzhu-wandushou")
                return notify_fail("你沒有準備使用千蛛萬毒手，無法施展萬蠱噬天。\n");

        skill = me->query_skill("qianzhu-wandushou", 1);

        if (skill < 220)
                return notify_fail("你的千蛛萬毒手修為有限，無法施展萬蠱噬天。\n");

        if (me->query_skill("force") < 300)
                return notify_fail("你的內功火候不夠，難以施展萬蠱噬天。\n");

        if( query("max_neili", me)<3500 )
                return notify_fail("你的內力修為沒有達到那個境界，無法運轉內力施展萬蠱噬天。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠，現在無法施展萬蠱噬天。\n");

        if( query_temp("weapon", me) )
                return notify_fail("你必須是空手才能施展萬蠱噬天。\n");

        msg = RED "\n$N" RED "仰天一聲長嘯，強催內勁，全身"
              "竟浮現出隱隱碧綠之色。喝道：“萬蠱噬天”,雙"
              "掌猛\n然拍出，登時幻出漫天碧綠色掌影，毒氣彌"
              "漫，籠罩$n" RED "全身！\n\n" NOR;

        message_combatd(msg, me, target);

        addn("neili", -300, me);
        addn_temp("apply/parry", skill, target);
        addn_temp("apply/dodge", skill, target);
        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, 0);
        }
        addn_temp("apply/parry", -skill, target);
        addn_temp("apply/dodge", -skill, target);
        me->start_busy(1 + random(2));

        return 1;
}