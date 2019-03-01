// This program is a part of NT MudLIB

#include <ansi.h>
void remove_effect(object me,int count);

int exert(object me)
{
        /*
        if ( !me->is_fighting())
                return notify_fail("你只能在戰鬥中使用「金剛不壞體神功」！\n");
        */

        if( (int)me->query_skill("yijinjing", 1) < 400 )
                return notify_fail("你的易筋經內功修為不夠，無法使用「金剛不壞體神功」！\n");

        if (me->query_skill_mapped("force") != "yijinjing")
                return notify_fail("其它內功有「金剛不壞體神功」嗎？\n");

        if( (int)me->query_con() < 40 )
                return notify_fail("你的根骨太低，根本無法使用「金剛不壞體神功」！\n");

        if( query("neili", me)<1000 )
                return notify_fail("你目前的內力太少了，無法使用「金剛不壞體神功」！\n");

        if( query("max_neili", me)<3800 )
                return notify_fail("你的內力修為這麼差，還想使用「金剛不壞體神功」？\n");

        if( query_temp("jin", me) )
                return notify_fail("你正在運用着呢！\n");

        if( query_temp("sl/jiuyang", me) )
                return notify_fail("你正在運用「少林九陽神功」！\n");

        message_combatd(HIY"\n$N突然深吸一口氣，目露慈光，面帶微笑，內力運轉，竟使全身上下寶光流動，是「金剛不壞體神功」！\n\n" NOR, me);
        me->start_busy(1);

        set_temp("jin", 1, me);
        set_temp("nopoison", 1, me);
        addn_temp("apply/armor", me->query_skill("yijinjing",1), me);
        addn("neili", -500, me);

        call_out("remove_effect", 1, me, me->query_skill("yijinjing", 1)/2+20);

        return 1;
}

void remove_effect(object me, int count)
{
        if( !me) return;
        if (count < 0)
        {
                delete_temp("nopoison", me);
                delete_temp("jin", me);
                addn_temp("apply/armor", -me->query_skill("yijinjing",1), me);
                message_vision(HIR"\n$N雙手合十，散去了凝聚於全身上下的「金剛不壞體神功」。\n"NOR, me);
                return;
        }
        else {
                call_out("remove_effect", 1, me,count -1);
        }
}

int help(object me)
{
        write(HIY"\n易筋經之「金剛不壞體神功」："NOR"\n");
        write(@HELP
        金剛，堅利之意，歷百劫千生，流轉六道，而覺性不壞。即以金剛之堅，喻
        般若體；以金剛之利，喻般若用。金剛不壞體神功為少林第一大絕技，以易
        筋經為本，使神、體、氣三者相融，循序漸進，持之以恆，便能抵禦心魔，
        抗擊外力。

        要求：  易筋經等級 200 以上；
                根骨 40 以上；
                最大內力 3800 以上；
                內力 1000 以上。
HELP
        );
        return 1;
}