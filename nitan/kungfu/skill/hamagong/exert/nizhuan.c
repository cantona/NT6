// This program is a part of NITAN MudLIB
// nizhuan.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        object weapon;
        int skill;
        string msg;

        if( userp(me) && !query("reborn/times", me) )
                return notify_fail("你所使用的內功中沒有這種功能。\n");

        /*
        if( query("family/family_name", me) != "歐陽世家" )
                return notify_fail("你不是歐陽世家弟子，無法使用逆轉九陰。\n");
        */

        if((int)me->query_skill("hamagong", 1) < 1000)
                return notify_fail("你的蛤蟆功不夠嫻熟，不會逆轉九陰。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的內力不夠。\n");

        if( query("jingli", me)<500 )
                return notify_fail("你的精力不夠。\n");

        if( query_temp("hmg_nizhuan", me) )
                return notify_fail("你已經逆運了九陰。\n");

        skill = me->query_skill("hamagong", 1);
        msg = HIB "$N" HIB "雙手撐地，口中發出一連竄低喉聲，一股股內勁勃發使$N" HIB "雙足離地，呈頭下足上之勢。。\n" NOR;
        message_combatd(msg, me);
        tell_object(me, HIW "你感覺體內蛤蟆功隨九陰逆轉，好像有股巨大的力量要崩發出來一樣。\n" NOR);

        addn_temp("apply/ap_power", 50, me);
        addn_temp("apply/add_damage", 50, me);
        addn_temp("apply/attack", skill, me);
        addn_temp("apply/avoid_xuruo", 50, me);
        addn_temp("apply/str", skill/4, me);
        set_temp("hmg_nizhuan", skill, me);
        addn("neili", -300, me);
        addn("jingli", -50, me);
        me->start_call_out( (: call_other, this_object(), "remove_effect", me, skill :), skill);
        if(me->is_fighting())
                me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( !me ) return;

        addn_temp("apply/str", -amount/4, me);
        addn_temp("apply/attack", -amount, me);
        addn_temp("apply/ap_power", -50, me);
        addn_temp("apply/add_damage", -50, me);
        addn_temp("apply/avoid_xuruo", -50, me);
        delete_temp("hmg_nizhuan", me);

        tell_object(me, HIW "你逆轉九陰運功過久，經脈又漸漸復原。\n" NOR);
}
