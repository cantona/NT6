// This program is a part of NITAN MudLIB
// jingsng.c 金剛拳 大金剛神通

#include <ansi.h>

inherit F_SSERVER;

void remove_effect(object me, int aamount, int damount);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int d_count, count, qi, maxqi, skill;

        if( query_temp("jingang", me) )
                return notify_fail("你已經在運功中了。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail("「大金剛神通」只能對戰鬥中的對手使用。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠，無法施展「大金剛神通」！\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功修為不夠，不能使用大金剛神通！\n");

        if ((int)me->query_skill("cuff") < 150)
                return notify_fail("你的拳法還不到家，無法使用大金剛神通！\n");

        if (me->query_skill_mapped("cuff") != "jingang-quan")
                return notify_fail("你沒有激發金剛拳，無法使用大金剛神通！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "$N" HIY "使出大金剛拳的絕技「大金剛神通」，臂力陡然增加！\n" NOR;

        qi=query("qi", me);
        maxqi=query("max_qi", me);
        skill = (int) (me->query_skill("jingang-quan", 1) / 3);
        count = me->query_str();
        d_count = (int)me->query_dex() / 2;

        if (qi > (maxqi * 0.4))
        {
                message_combatd(msg, me, target);

                addn_temp("apply/str", count*2, me);
                addn_temp("apply/dex", -d_count, me);
                set_temp("jingang", 1, me);
                me->start_call_out((: call_other, __FILE__, "remove_effect", me, count * 2, d_count :), skill);

                addn("neili", -150, me);
        } else
        {
                msg = HIR "$N" HIR "拼盡畢生功力使出了大金剛拳的終"
                      "極絕技, 全身骨骼一陣爆響, 欲與$n" HIR "同歸於盡！\n" NOR;
                message_combatd(msg, me, target);
                addn_temp("apply/str", count*9, me);
                set_temp("jingang", 1, me);

                COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);
                set("neili", 0, me);
                addn("max_neili", -10, me);

                msg = HIR "$N" HIR "用盡了最後一點氣力, 噴出一口鮮血, 一頭栽倒在地！\n" NOR;
                message_combatd(msg, me, target);
                addn_temp("apply/str", -(count*9), me);
                delete_temp("jingang", me);
                me->unconcious();
        }
        return 1;
}

void remove_effect(object me, int aamount, int damount)
{
        if( query_temp("jingang", me) )
        {
                addn_temp("apply/str", -aamount, me);
                addn_temp("apply/dex", damount, me);
                delete_temp("jingang", me);
                tell_object(me, "你的大金剛神通運行完畢，將內力收回丹田。\n");
        }
}
