
#include <ansi.h>

inherit F_SSERVER;
int remove_effect(object me, object target);
string name() { return "同歸劍法"; }

int perform(object me, object target)
{
        string weapon;
        int skill;
        int ap, dp, damage;
        string msg;

        if( !target ) target = offensive_target(me);

        if( !target
        ||        !target->is_character()
        ||        !me->is_fighting(target) )
                return notify_fail("同歸劍法只能對戰鬥中的對手使用。\n");

        if( query_temp("tonggui", me) )
                return notify_fail("你已在使用同歸劍法！\n");

        if( query("eff_qi", me)>query("max_qi", me)*2/3 )
                return notify_fail("你好端端的，跟人家同歸幹什麼？\n");

        if( me->query_skill_mapped("force") != "xiantian-gong" )
                return notify_fail("你所用的並非先天功，無法施展同歸劍法！\n");

        if( me->query_skill("xiantian-gong",1) < 100 )
                return notify_fail("你的先天功火候未到，無法施展同歸劍法！\n");


        if( me->query_skill("sword") < 135 )
                return notify_fail("你的全真劍法修為不足，還不會使用同歸劍法！\n");

        if( query("neili", me) <= 100 )
                return notify_fail("你的內力不夠使用同歸劍法！\n");
        if( query("jingli", me) <= 150 )
                return notify_fail("你的精力不夠使用同歸劍法！\n");


        msg = HIY"$N使出「同歸劍法」，劍氣縱橫，只攻不守，招招拼命，兇狠危險之至！\n" NOR;
        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");
        if( ap / 2 + random(ap) > dp )
        {
                me->start_busy(2);
                if( !target->is_busy() )
                        target->start_busy(random(3));
                damage=query("qi", target);
                target->receive_damage("qi", damage-10,me);
                target->receive_wound("qi", damage-10,me);
                msg += HIC "$n疾忙斜躍，但劍急如電，只覺一陣鑽心劇痛，劍尖紮入胸前，鮮血飛濺！\n"NOR;
                set("neili", 0, me);
        }
        else
        {
                me->start_busy(2);
                set("neili", 100, me);
                msg += HIY"可是$n微微一笑，氣定神閒，身形輕變，閃過劍招。\n"NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}
