
// daxiao.c

#include <ansi.h>

int exert(object me, object target)
{
        int level = me->query_skill("linji-zhuang", 1);
        int amount;

        if (level < 150) return notify_fail("你的臨濟十二莊修為還不夠。\n");

        if( query("max_neili", me)<5*level )
                return notify_fail("你的內力還不夠強。\n");

        if( query("neili", me)<4*level )
                return notify_fail("你的真氣不夠。\n");

        if( query("eff_qi", me)<query("max_qi", me) )
                return notify_fail("你現在氣血受傷，只怕無法調節精氣平衡！\n");

        if( query("eff_jing", me)<query("max_jing", me) )
                return notify_fail("你現在精神受傷，只怕無法調節精氣平衡！\n");

        if( query_temp("linji/daxiao", me) )
                return notify_fail("你已經運功調節精氣大小了。\n");

        set_temp("linji/daxiao", 1, me);
        write( HIY "你屏息靜氣，交錯運行大小二莊，只覺一股暖流出天門，穿地戶，沿著全身經脈運行一周，匯入丹田氣海。\n" NOR);
        message_combatd(
                HIY + "只見" + me->name() + "屏息靜氣，頭頂飄起一縷縷白氣，神態略現疲乏。\n" NOR,
                me);

        amount=query("max_jing", me)-query("max_qi", me);
        amount /= 2;

        addn("max_qi", amount, me);
        addn("max_jing", -amount, me);
        set("eff_qi",query("max_qi",  me), me);
        set("eff_jing",query("max_jing",  me), me);
        if( query("qi", me)>query("max_qi", me) )
                set("qi",query("max_qi",  me), me);
        if( query("jing", me)>query("max_jing", me) )
                set("jing",query("max_jing",  me), me);

        addn("neili", -4*level, me);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, amount :), 1800);

        return 1;
}

void remove_effect(object me, int level)
{
        addn("max_qi", -level, me);
        addn("max_jing", level, me);
        set("eff_qi",query("max_qi",  me), me);
        set("eff_jing",query("max_jing",  me), me);
        if( query("qi", me)>query("max_qi", me) )
                set("qi",query("max_qi",  me), me);
        if( query("jing", me)>query("max_jing", me) )
                set("jing",query("max_jing",  me), me);
        delete_temp("linji/daxiao", me);

        tell_object(me, HIG"你行大小二莊已久，又恢復了原有精氣。\n"NOR);
}