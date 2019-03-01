// This program is a part of NITAN MudLIB
// tong.c 天地同壽

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string name() { return "天地同壽"; }

int perform(object me, object target)
{
        string msg;
        object weapon;
        int ap, dp;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("天地同壽只能對戰鬥中的對手使用。\n");

        if( me->is_busy() )
                return notify_fail("你現在忙著呢，使不出這一招。\n");

        weapon=query_temp("weapon", me);
        if( !weapon || query("skill_type", weapon) != "sword" )
                return notify_fail("你手中無劍，如何使得天地同壽？\n");

        if( (int)me->query_skill("sword") < 150 )
                return notify_fail("你的太極劍法極不夠嫻熟，不會使用天地同壽。\n");

        if( (int)me->query_skill("taiji-shengong", 1) < 120 )
                return notify_fail("你的太極神功修為不夠，不會使用天地同壽。\n");

        if( me->query_skill_mapped("force") != "taiji-shengong")
                return notify_fail("你所用的內功與太極劍意氣路相悖！\n");

        ap=me->query_int()+me->query_str()+query("level", me)*20+
             me->query_dex() + me->query_con();

        if( query("shen", me)>query("shen", target)*3/2 )
                ap *= 3;
                ap /= 2;
        dp=target->query_int()+target->query_str()+query("level", target)*20+
             target->query_dex() + target->query_con();

        msg = HIW "$N" HIW "一聲悲嘯，背心空門大開，飛撞向$n" HIW "懷中，倒轉劍柄向自己小腹直插而下！！！\n" NOR;
        me->want_kill(target);
        me->start_busy(1 + random(2));

        if( ap / 2 + random(ap) > dp )
        {
                msg += HIR "$n" HIR "猝不及防之下，被$N" HIR "撞入懷中，只覺小腹一涼，" NOR + weapon->name() +
                       HIR "已自$N" HIR "後背透體而入！！！\n" NOR;
                message_combatd(msg, me, target);
                target->die(me);
                me->die(target);
                return 1;
        } else
        {
                msg += HIC "$n" HIC "不料$N" HIC "用此招數，手忙腳亂，狼狽萬狀的躲閃開去，但已嚇得手足冰涼，好一陣動彈不得。\n" NOR;
                me->die(target);
                if( !target->is_busy() )
                        target->start_busy(3 + random(3));
        }

        message_combatd(msg, me, target);

        return 1;
}
