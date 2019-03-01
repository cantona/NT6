// tiandi.c

#include <ansi.h>

int exert(object me, object target)
{
        int level = me->query_skill("linji-zhuang", 1);

        if (level < 30) return notify_fail("你的臨濟十二莊修為還不夠。\n");

        if (me->is_fighting())
                return notify_fail("戰鬥中不能運用天地二莊。\n");

        if( query("max_neili", me)<5*level )
                return notify_fail("你的內力還不夠強。\n");

        if( query("neili", me)<4*level )
                return notify_fail("你的真氣不夠。\n");

        if( query("eff_qi", me)<query("max_qi", me)/2 )
                return notify_fail("你已經受傷過重，只怕一運真氣便有生命危險！\n");

        if( query_temp("linji/tiandi", me) )
                return notify_fail("你已經運用天地二莊聚精氣于身了。\n");

        set_temp("linji/tiandi", 1, me);
        write( HIY "你席地而坐，五心向天，運行天地二莊，益氣升陽，益陰潛陽，升降反正，天地二氣交泰于身，頓覺自己精氣上限增加了。\n" NOR);
        message_combatd(
                HIY + "只見" + me->name() + "席地而坐，五心向天，臉上紅光時隱時現，不一會兒便神採弈弈地站了起來。\n" NOR,
                me);

        addn("max_qi", level*10, me);
        addn("max_jing", level*10, me);
        me->receive_curing("qi", level*10);
        me->receive_curing("jing", level*10);
        addn("jingli", level, me);
        addn("neili", -4*level, me);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, level :), 1800);

        return 1;
}

void remove_effect(object me, int level)
{
        addn("max_qi", -level*10, me);
        addn("max_jing", -level*10, me);
        if( query("eff_qi", me)>query("max_qi", me) )
                set("eff_qi",query("max_qi",  me), me);
        if( query("eff_jing", me)>query("max_jing", me) )
                set("eff_jing",query("max_jing",  me), me);
        delete_temp("linji/tiandi", me);

        tell_object(me, HIG"你所聚天地之精氣已散回天地之間，你又恢復了原有精氣。\n"NOR);
}