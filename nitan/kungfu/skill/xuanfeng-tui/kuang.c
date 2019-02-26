#include <ansi.h>
#include <combat.h>

string name() { return HIY "狂風絕技" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int count;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("xuanfeng-tui", 1) < 100)
                return notify_fail("你旋風掃葉腿不夠嫻熟，難以施展" + name() + "。\n");

        if ((int)me->query_skill("xuanfeng-tui", 1) < 100)
                return notify_fail("你的旋風掃葉腿不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("unarmed") != "xuanfeng-tui")
                return notify_fail("你沒有激發旋風掃葉腿，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("unarmed") != "xuanfeng-tui")
                return notify_fail("你沒有準備旋風掃葉腿，難以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "$N" HIY "使出桃花島狂風絕技，身法飄忽不定，足帶風塵，掌攜"
              "萬鈞，有若天仙！\n" NOR;
        message_combatd(msg, me);
        addn("neili", -100, me);

        count = me->query_skill("bibo-shengong", 1) / 2 + me->query_skill("xuanfeng-tui", 1);
        addn_temp("apply/attack", count, me);

        msg = YEL  "\n$N" YEL"聚力於左掌，右腿一腳跟着踢出！\n"NOR;
        message_combatd(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

        msg = HIM  "人影中，" HIM "$N" HIM "翻身而起，左掌大力得揮向$n！\n"NOR;
        message_combatd(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

        msg = YEL "\n$N" YEL "見" YEL "$n" YEL "門户大開，暗運內力，雙腿連環踢向" YEL "$n！\n"NOR;
        message_combatd(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

        msg = HIM  "$N" HIM "越戰越勇，周圍驟起一陣旋風，使得" HIM "$n" CYN "看不清方向！\n"NOR;
        message_combatd(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

        msg = YEL "\n$N" YEL "如星光乍現，右掌略帶悠然之色輕拍" YEL "$n！\n"NOR;
        message_combatd(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

        msg = HIM "$N" HIM "長嘯一聲，面如赤發，忽然轉到" HIM "$n" HIM"身後，反手又是一掌！\n"NOR;
        message_combatd(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

        addn("neili", -100, me);
        me->start_busy(1 + random(2));
        addn_temp("apply/attack", -count, me);
        return 1;
}