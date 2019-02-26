
// fengyun.c

#include <ansi.h>

int exert(object me, object target)
{
        int level = me->query_skill("linji-zhuang", 1);

        if (level < 120) return notify_fail("你的臨濟十二莊修為還不夠。\n");

        if( query("max_neili", me)<5*level )
                return notify_fail("你的內力還不夠強。\n");

        if( query("neili", me)<4*level )
                return notify_fail("你的真氣不夠。\n");

        if( query("eff_qi", me)<query("max_qi", me)/2 )
                return notify_fail("你已經受傷過重，只怕一運真氣便有生命危險！\n");

        if( query_temp("linji/fengyun", me) )
                return notify_fail("你此時四肢百骸真氣鼓盪，不必再次運功。\n");

        set_temp("linji/fengyun", 1, me);
        write( HIY "你暗運風雲兩莊，心思浮雲飄空之悠閒緩慢，默想狂風蕩地之迅速緊急，\n一股丹田熱氣分注四肢百骸，但覺身手敏捷了許多。\n" NOR);
        message("vision",
                HIY + "只見" + me->name() + "微閉雙眼，身旁凝起一圈白霧，瞬息間一股旋風捲過，"+me->name()+"身形又復清晰。\n" NOR,
                environment(me), me);

        addn("neili", -level, me);
        level /= 10;
        addn_temp("apply/dex", level, me);
        addn_temp("apply/attack", -level/2, me);
        addn_temp("apply/armor", level*15, me);
        addn_temp("apply/defense", level*5, me);

        me->start_call_out( (: call_other, __FILE__, "recover", me, level :), level * 10);

        return 1;
}

void recover(object me, int level)
{
        addn_temp("apply/dex", -level, me);
        addn_temp("apply/attack", level/2, me);
        addn_temp("apply/armor", -level*15, me);
        addn_temp("apply/defense", -level*5, me);
        delete_temp("linji/fengyun", me);

        tell_object(me, HIG"你風雲行功已久，略覺步履沉重了一些。\n"NOR);
}