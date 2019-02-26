// longhe.c

#include <ansi.h>

int exert(object me, object target)
{
        int level = me->query_skill("linji-zhuang", 1);
        int jingli, jing, extrajing;

        if (level < 90) return notify_fail("你的臨濟十二莊修為還不夠。\n");

        if( query("max_neili", me)<5*level )
                return notify_fail("你的內力還不夠強。\n");

        if( query("eff_qi", me)<query("max_qi", me)/2 )
                return notify_fail("你已經受傷過重，只怕一運真氣便有生命危險！\n");

        if( query("eff_jing", me)<query("max_jing", me)/2 )
                return notify_fail("你已經受傷過重，只怕一運真氣便有生命危險！\n");

        extrajing=query("jing", me)-query("max_jing", me)/2;
        if (extrajing < 1)
                return notify_fail("你的精神太差。");

        if( query("neili", me)<1 )
                return notify_fail("你的真氣不夠。\n");

        jingli=query("max_jingli", me)-query("jingli", me);
        if ( jingli < 10 )
                return notify_fail("你現在精力充沛。\n");
        jing = 90*jingli/level;
        if (jing < 5) jing = 5;
        if (extrajing < jing) {
                jingli = jingli * extrajing / jing;
                jing = extrajing ;
        }
        addn("jing", -jing, me);
        addn("jingli", jingli, me);

        write( HIY "你暗運龍鶴兩莊，啟天門，閉地户，聚精成力，頓覺氣力倍增。\n" NOR);
        message("vision",
                HIY + "只見" + me->name() + "稍顯疲乏，但轉瞬間便精神抖擻。\n" NOR,
                environment(me), me);

        return 1;
}