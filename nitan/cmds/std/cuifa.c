// cuifa.c

inherit F_SSERVER;
#include <ansi.h>
void sanshi(object me, object target);

int main(object me, string arg)
{
        object target;
        if( me->is_fighting() ) return notify_fail("戰鬥中催發？找死嗎？\n");
        if( query("family/master_id", me) != "renwoxing" )
                return notify_fail("你不是任教主的弟子，無法催發丹藥！\n");
        if(me->is_busy())
                return notify_fail("你正忙著呢！\n");
        if((int)me->query_skill("xixing-dafa", 1) < 100)
                return notify_fail("你的吸星大法修為還不夠。\n");
        if((int)me->query_skill("kuihua-xinfa", 1) < 100)
                return notify_fail("你的葵花心法修為太低。\n");
        if( query("qi", me)<300 )
                return notify_fail("你的氣不夠。\n");
        if( query("neili", me)<400 )
                return notify_fail("你的真氣不夠。\n");
        if( query("eff_qi", me)<query("max_qi", me)/2 )
                return notify_fail("你受傷過重，只怕一運真氣便有生命危險！\n");
        if ( !arg ) return notify_fail("你要催發誰身上的丹藥？\n");
        if ( present(arg, environment(me)) )
                return notify_fail("你要催發的人就在你身邊，不怕被砍？\n");
        target = find_player(arg);
        if (!target) target = find_living(arg);
        if (!target || !me->visible(target)) return notify_fail("你要催發的人現在沒在吧？\n");

        write( HIW "你盤膝坐下來開始催發三屍腦神丹。\n" NOR);
        message("vision", HIW + me->name() + "運起吸星大法，盤膝坐下，開始催發三屍腦神丹。\n" NOR, environment(me), me);
        addn("neili", -300, me);
        me->start_busy(5);
        me->start_call_out( (: call_other,__FILE__,"sanshi",me,target :),5);
        return 1;
}
void sanshi(object me, object target)
{
        message_vision("$N盤膝而坐，嘴裡不知道念叨著什麼。\n",me);
        if( !query("sanshi", target) )
        {
                tell_object(me,"你忽然覺得不對頭，"+query("name", target)+"體內沒有被種屍蟲！\n");
                return;
        }
        if( query("sanshi", target) != query("id", me) )
        {
                tell_object(me,"你忽然覺得不對頭，"+query("name", target)+"體內種的不是你的屍蟲！\n");
                return;
        }
        tell_object(target, "你忽然覺得頭不知什麼原因疼了起來，漸漸痛不可抑。猛然想起是屍蟲發作，只覺得頭腦一轟，就什麼也不知道了！\n");
//        target->die();
        delete("sanshi", target);
        target->receive_wound("qi", 10000,"三屍腦神丹突發而亡。真是可惜。");
        target->receive_damage("qi", 10000,"三屍腦神丹突發而亡。真是可惜。");
        target->receive_wound("jing", 10000,"三屍腦神丹突發而亡。真是可惜。");
        target->receive_damage("jing", 10000,"三屍腦神丹突發而亡。真是可惜。");
//message("channel:rumor", MAG"【謠言】某人："+target->query("name")+"三屍腦神丹突發而亡。真是可惜！\n"NOR, users());
        return;
}

int help(object me)
{
        write(@HELP
指令格式 : cuifa <人物>
 
    這個指令讓你催發一個人物身上的三屍腦神丹。當然，只有吃了
你的三屍腦神丹的人才會被你催發。

HELP
        );
        return 1;
}
 