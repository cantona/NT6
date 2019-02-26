#include <ansi.h>
#include <combat.h>

#define CHI "「" HIR "赤煉神刀" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int count;
        int i;

        if( userp(me) && !query("can_perform/xuedao-dafa/chi", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(CHI "只能對戰鬥中的對手使用。\n");
 
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對，難以施展" CHI "。\n");

        if ((int)me->query_skill("force") < 220)
                return notify_fail("你的內功火候不夠，難以施展" CHI "。\n");

        if ((int)me->query_skill("xuedao-dafa", 1) < 160)
                return notify_fail("你的血刀大法還不到家，難以施展" CHI "。\n");

        if (me->query_skill_mapped("force") != "xuedao-dafa")
                return notify_fail("你沒有激發血刀大法為內功，難以施展" CHI "。\n");

        if (me->query_skill_mapped("blade") != "xuedao-dafa")
                return notify_fail("你沒有激發血刀大法為刀法，難以施展" CHI "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真氣不夠，難以施展" CHI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "$N" HIW "嗔目大喝，手中" + weapon->name() + HIW "一勢「"
              HIR "赤煉神刀" HIW "」迸出漫天血光，鋪天蓋地灑向$n" HIW "。\n" NOR;

        if (random(me->query_skill("blade")) > target->query_skill("parry") / 2)
        {
                msg += HIR "霎時間$n" HIR "只覺周圍四處殺氣瀰漫，全身氣血翻"
                       "滾，甚難招架。\n" NOR;
                count = me->query_skill("xuedao-dafa", 1) / 4;
        } else
        {
                msg += HIY "霎時間$n" HIY "只覺周圍四處殺氣瀰漫，心底微微一"
                       "驚，連忙奮力招架。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn_temp("apply/attack", count, me);
        addn("neili", -150, me);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(6));
        return 1;
}