// This program is a part of NITAN MudLIB
// jue.c 烈火三絕劍

#include <ansi.h>

inherit F_SSERVER;

string name() { return "烈火三絕劍"; }

int perform(object me, object target)
{
        object weapon, ob;
        string msg;
        int i;

        if (! me->is_fighting())
                return notify_fail("「"+HIR"烈火三絕劍"NOR+"」只能在戰鬥中使用。\n");

        if (me->is_busy())
                return notify_fail("你正忙著呢！\n");

        if (! objectp(weapon = query_temp("weapon", me))
        || (string)query("skill_type", weapon) != "sword")
                return notify_fail("你使用的武器不對。\n");

        if ((int)query("neili", me) < 500)
                return notify_fail("你的真氣不夠！\n");

        if ((int)me->query_skill("sword") < 100 ||
                me->query_skill_mapped("sword") != "liehuo-jian")
                return notify_fail("你的「烈火劍」還不到家，無法使用「"+HIR"烈火三絕劍"NOR+"」！\n");

        msg = HIR "$N運起內力，頓時手中兵器火燄逼人，接著向對方連環刺去！\n" NOR;
        message_combatd(msg, me, target);

        me->clean_up_enemy();
        ob = me->select_opponent();
        addn("neili", -300, me);

        for(i = 0; i < 3; i++)
                if (me->is_fighting(ob) && ob->is_fighting(me) && query("eff_qi", ob)>0)
                {
                        set("action_msg", "緊跟著", me);
                        if (!query("equipped", weapon)) break;
                        COMBAT_D->do_attack(me, ob,weapon, 0);
                } else break;

        me->start_busy(1 + random(2));
        return 1;
}
