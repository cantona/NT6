// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "五輪連轉" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string wp, msg;
        int i, count;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "hammer" )
                return notify_fail("你所使用的武器不對，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("hammer") != "riyue-lun")
                return notify_fail("你沒有激發日月輪法，難以施展" + name() + "。\n");

        if ((int)me->query_skill("riyue-lun", 1) < 150)
                return notify_fail("你日月輪法火候不足，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 250)
                return notify_fail("你的內功火候不足，難以施展" + name() + "。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的內力修為不足，難以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        wp = weapon->name();

        msg = HIY "$N" HIY "嗔目大喝，施展出日月輪法「" HIW "五輪連轉"
              HIY "」神技，驀地將手中" + wp + HIY "飛擲\n而出，幻作數"
              "道光芒，相互盤旋着壓向$n" HIY "，招術煞為精奇！\n" NOR;
        message_combatd(msg, me, target);

        if ((int)me->query_skill("longxiang-gong", 1) < 90)
                count = me->query_skill("force", 1) / 8;
        else
                count = me->query_skill("longxiang-gong", 1) / 4;

        addn_temp("apply/attack", count, me);
        addn_temp("apply/damage", count*2/3, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (! weapon->is_item_make()
                    && query("id", weapon) == "riyue jinlun" )
                {
                        switch (i)
                        {
                        case 0:
                                msg = WHT "突然間錫輪從日月金輪中分離"
                                      "開來，化作一道灰芒朝$n" WHT "砸"
                                      "去。\n" NOR;
                                break;
                        case 1:
                                msg = HIR "突然間鐵輪從日月金輪中分離"
                                      "開來，化作一道紅芒朝$n" HIR "砸"
                                      "去。\n" NOR;
                                break;
                        case 2:
                                msg = YEL "突然間銅輪從日月金輪中分離"
                                      "開來，化作一道黃芒朝$n" YEL "砸"
                                      "去。\n" NOR;
                                break;
                        case 3:
                                msg = HIW "突然間銀輪從日月金輪中分離"
                                      "開來，化作一道銀芒朝$n" HIW "砸"
                                      "去。\n" NOR;
                                break;
                        default:
                                msg = HIY "突然間金輪從日月金輪中分離"
                                      "開來，化作一道金芒朝$n" HIY "砸"
                                      "去。\n" NOR;
                                break;
                        }
                        message_combatd(msg, me, target);
                        COMBAT_D->do_attack(me, target, weapon, 30);
                } else
                        COMBAT_D->do_attack(me, target, weapon, 0);
        }
        addn("neili", -250, me);
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count*2/3, me);
        me->start_busy(1 + random(3));
        return 1;
}

