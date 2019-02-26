#include <ansi.h>
#include <combat.h>

#define DAN "「" HIR "彈射毒藥" NOR "」"

inherit F_SSERVER;

int exert(object me, object target)
{
        object du;
        int lvl, lvp, damage, pos;
        int an, dn, ap, dp;
        string name, msg;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

                if (! target || ! me->is_fighting(target))
                        return notify_fail(DAN "只能在戰鬥中對對手使用。\n");

        lvl = me->query_skill("jiuyin-hamagong", 1);
        lvp = me->query_skill("poison");

        if (lvl < 160)
                return notify_fail("你的蛤蟆功不夠嫻熟，難以施展" DAN "。\n");

        if (lvp < 180)
                return notify_fail("你對毒技的瞭解不夠，難以施展" DAN "。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的內力修為不足，難以施展" DAN "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在的內息不足，難以施展" DAN "。\n");

        // 任務NPC可以直接施展
        if( userp(me) && !objectp(du=query_temp("handing", me)) )
                return notify_fail("你必須拿着(hand)些毒藥才能施展" DAN "。\n");

        if (objectp(du) && ! mapp(query("poison",du))) 
                return notify_fail("你手中所拿的" + du->name() + NOR "不"
                                   "是毒藥，難以施展" DAN "。\n");

        if( objectp(du) && query("no_shot", du) )
                return notify_fail("將" + du->name() + NOR "彈射出去？似"
                                   "乎不太好吧。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        if (objectp(du))
                name = du->name();
        else
                name = NOR + RED "毒丸";

        msg = HIR "$N" HIR "默運內功，施出蛤蟆功絕招「" HIR "彈射毒藥"
              HIR "」，將手中" + name + HIR "「嗖」地彈向$n" HIR "。\n" NOR;

        an=query("max_neili", me)+query("neili", me)/4;
        dn=query("max_neili", target)+query("neili", target)/4;

        // 首先判斷內力，如果對方內力過高則無效
        if (an * 3 / 5 + random(an) < dn)
        {
                msg += WHT "然而$n" WHT "全然不放在心上，輕輕一抖，已將$N"
                       WHT "射來毒丸打落。\n" NOR;
                me->start_busy(3);
                addn("neili", -150, me);
        } else
        {
                ap = me->query_skill("force") +
                     me->query_skill("poison");

                // 將任務NPC和玩家區分，再計算防禦狀況
                if (userp(me))
                        dp = target->query_skill("dodge") +
                             target->query_skill("martial-cognize");
                else
                        dp = target->query_skill("dodge") +
                             target->query_skill("parry");

                damage = pos / 2 + random(pos / 2);

                if (ap / 2 + random(ap) > dp)
                {
                        msg += HIR "$n" HIR "一個不慎，毒丸已經射入體內，頓時痛苦不堪。\n" NOR;

                        COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 55, " ");
                             
                        target->affect_by("baituo_poison",
                        ([ "level"    : lvp + random(lvp),
                           "id":query("id", me),
                           "duration" :40 + random(lvp / 20) ]));

                        target->receive_damage("jing", damage / 2, me);
                        target->receive_wound("jing", damage / 3, me);

                        me->start_busy(2);
                        addn("neili", -200, me);
                } else
                {
                        msg += CYN "可是$n" CYN "見勢不妙，急忙騰挪身形，終"
                               "於避開了$N" CYN "射來的毒丸。\n" NOR;
                        me->start_busy(3);
                        addn("neili", -100, me);
                }
        }
        message_combatd(msg, me, target);

        // 消耗毒藥數量
        if (objectp(du))
        {
                if (du->query_amount())
                {
                        du->add_amount(-1);

                        if (du->query_amount() < 1)
                                destruct(du);
                } else
                        destruct(du);
        }
        return 1;
}
