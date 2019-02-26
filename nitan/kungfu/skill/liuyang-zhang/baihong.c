// This program is a part of NITAN MudLIB
// baihong.c 「白虹掌力」

/*
李秋水得虛竹援手，避過了童姥的急攻，內息已然調勻，説道：“夢郎，我
已不礙事，你讓開吧。”左掌拍出，右掌一帶，左掌之力繞過虛竹身畔，向
童姥攻去。童姥心下暗驚：“這賤人竟然練成了‘白虹掌力’，曲直如意，
當真了得。”當即還掌相迎。
*/

#include <ansi.h>

string name() { return "白虹掌力"; }

void remove_effect(object me,int strike);

int perform(object me, object target)
{
        int strike;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("只能對戰鬥中的對手使用。\n");


        if( query_temp("yield", me) )
                return notify_fail("你不出招，如何使出「白虹掌力」？\n");

        if( query_temp("lingjiu/baihong", me) )
                return notify_fail("你已經在使用「白虹掌力」了！\n");

        if ( me->query_skill_mapped("force") != "xiaowu-xiang"
                && me->query_skill_mapped("force") != "bahuang-gong"
                && me->query_skill_mapped("force") != "beiming-shengong")
                return notify_fail("你所用的內功與「白虹掌力」心法相悖！\n");

        if( (int)me->query_skill("strike", 1) < 120 )
                return notify_fail("你的掌法修為還不夠，難以施展「白虹掌力」！\n");

        if( (int)me->query_skill("force", 1) < 120 )
                return notify_fail("你的內功修為火候未足，無法以把內力運用自如！\n");

        if( query("max_neili", me) <= 1500 )
                return notify_fail("你的內力不夠渾厚，內力無法運用自如！\n");

        if( query("neili", me) <= 500 )
                return notify_fail("你的內力不夠，內力無法運用自如！\n");

        if( query("jing", me) <= 200 )
                return notify_fail("你的精力有限，難以施展「白虹掌力」！\n");

        addn("neili", -100, me);
        addn("jing", -150, me);

        strike = me->query_skill("strike") / 2;

        addn_temp("apply/attack", strike, me);
        set_temp("lingjiu/baihong", strike, me);

        message_combatd(WHT "\n$N左掌拍出，右掌一帶，左掌之力吞吐不定。這門功夫乃是逍遙派上乘掌法中\n"
                            "的"+ HIW +"‘白虹掌力’"+ NOR + WHT +"，此刻$N掌力曲直如意，當真了得！\n" NOR, me);

        call_out("checking", 1, me, strike);
        return 1;
}

void checking(object me, int strike)
{
        if( !me ) return;

        if( !living(me) || me->is_ghost() )
        {
                remove_effect(me, strike);
                return;
        }
        else if( !me->is_fighting() && !me->is_busy() )
        {
                remove_effect(me, strike);
                message_combatd(WHT "\n$N左掌一揮，右掌在前胸畫了個弧，收起了吞吐不定的掌力。\n"NOR, me);
                me->start_busy(1);
                return;
        }
        else if( query("neili", me)<query("max_neili", me)/5 ||
                query("jing", me)<query("max_jing", me)/4 )
        {
                remove_effect(me, strike);
                tell_object(me, HIR "\n你微覺內息不暢，不得不將內力收回！\n" NOR);
                message_combatd(CYN "\n" + me->name() + CYN "雙掌一滯，掌力已不如之前遊走無常，變幻不定！\n" NOR,
                                me);
                me->start_busy(2);
                return;
        }
        else if( me->query_skill_mapped("strike") != "liuyang-zhang" && !me->is_busy() )
        {
                remove_effect(me, strike);
                message_combatd(CYN "\n$N圈轉手掌，突然變招，掌力已不如之前遊走無常，變幻不定！\n"NOR, me);
                return;
        }
        else if( query_temp("lingjiu/baihong", me) <= 50 )
        {
                remove_effect(me, strike);
                message_combatd(HIC "\n$N手掌圈轉，已堪堪將一路"+ HIW +"「白虹掌力」"+ HIC +"盡數使出！\n"NOR, me);
                return;
        }

        call_out("checking", 1, me, strike);
}

void remove_effect(object me, int strike)
{
        if (! objectp(me)) return;

        delete_temp("lingjiu/baihong", me);
        addn_temp("apply/attack", -strike, me);
}
