// lianhuan.c  瘋魔杖法之瘋魔飛杖

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "瘋魔飛杖"; }
void check_fight(object me, object target, object weapon);
private int remove_attack(object me, object weapon);

int perform(object me, object target)
{
        object weapon;
        int skill;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("瘋魔飛杖只能對戰鬥中的對手使用。\n");

        if( query_temp("fengmo", me) )
                return notify_fail("你已在使用瘋魔飛杖了！\n");

        weapon=query_temp("weapon", me);
        if( !objectp(weapon) || query("skill_type", weapon) != "staff" )
                return notify_fail("你手中無杖，如何能夠施展瘋魔飛杖？\n");

        if( me->query_skill_mapped("force") != "huntian-qigong" )
                return notify_fail("你所用的並非混天氣功，無法配合杖法施展瘋魔飛杖！\n");

        if( me->query_skill("force") < 100 )
                return notify_fail("你的混天氣功火候未到，無法配合杖法施展瘋魔飛杖！\n");

        if( me->query_skill("staff") < 100 )
                return notify_fail("你瘋魔杖法修為不足，還不會使用瘋魔飛杖！\n");

        if( query("neili", me) <= 300 )
                return notify_fail("你的內力不夠施展瘋魔飛杖！\n");
        if( query("jingli", me) <= 200 )
                return notify_fail("你的精力不夠施展瘋魔飛杖！\n");

        skill = me->query_skill("staff");

        message_combatd(HIR "\n$N大喝一聲將手中急轉着的"+weapon->name()+"脱手擲出，在空中高低左右迴旋！\n\n" NOR,
                        me, target);

        set_temp("fengmo", 1, me);
        set_temp("location", file_name(environment(me)), me);
        addn("neili", -200, me);
        addn("jingli", -100, me);
        me->start_busy(3);
        weapon->unequip();

        set("no_clean_up", 1, weapon);
        me->reset_action();
        call_out("check_fight", 0, me, target, weapon);

        return 1;
}

void check_fight(object me, object target, object weapon)
{
        string msg;
        int damage;

        if ( !objectp( me ) ) return;
                me->reset_action();

        if( query_temp("fengmo", me) >= me->query_skill("fengmo-zhang",1)/100 )
        {
                call_out("remove_attack", 1, me, weapon);
        }
        else if( me->is_fighting() && query_temp("fengmo", me) )
        {

                msg = HIM "\n突然間" + weapon->name() + HIM "自行向$n猛然飛撞過去！\n" NOR;

                if( random(query("level", me))>query("level", target)/2 )
                {
                        damage = 60 + random(me->query_skill("fengmo-zhang", 1) / 4);
                        target->receive_damage("qi", damage, me);
                        msg += HIR "$n只覺一股大力鋪天蓋地般壓來,登時眼前一花，兩耳轟鳴,哇的噴出一口鮮血！！\n" NOR;


                } else
                {
                        msg += YEL "$n看得分明，身形一讓，避過了" + weapon->name() + YEL "！\n" NOR;
                }
                message_combatd(msg, me, target);
                message_combatd(HIR "\n$N猛吸一口氣，飄身趕上$n伸掌在杖尾一推，將其又推在半空飛旋。\n\n" NOR,
                                me, weapon);

                addn_temp("fengmo", 1, me);
                call_out("check_fight", 1, me, target, weapon);
        } else
        {
                call_out("remove_attack", 1, me, weapon);

        }
}

int remove_attack(object me, object weapon)
{
        remove_call_out("check_fight");
        if ( !objectp( me ) ) return 1;
        delete_temp("fengmo", me);

        if( file_name(environment(me)) == query_temp("location", me) && living(me) )
        {
                weapon->move(me);
                set("no_clean_up", 0, weapon);
                weapon->wield();
                message_combatd(YEL "\n$N縱身上前，將飛旋的$n收回。\n\n" NOR, me, weapon);
        } else
        {
                weapon->move(query_temp("location", me));
                message("vision", "只聽得鏘的一聲，"+weapon->name()+"力盡由半空跌落。\n",
                        environment(weapon), ({weapon}) );
        }

        delete_temp("location", me);

        return 1;
}
