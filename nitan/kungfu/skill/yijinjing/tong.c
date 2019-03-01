// shield.c 易筋經 一氣通八脈

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill, qi, maxqi;


        if( query("family/family_name", me) != "少林派" )
                return notify_fail("你不是少林弟子，無法使用易筋經絕技。\n");

        if (target != me)
                return notify_fail("你只能用易筋經來激發一氣通八脈 \n");

        if ((skill = (int)me->query_skill("yijinjing", 1)) < 100)
                return notify_fail("你的易筋經等級不夠。\n");

        if( query("eff_qi", me)*100/query("max_qi", me)>80 )
                return notify_fail("你傷勢很輕，無法激勵易筋經至高絕學。\n");

        if( query("eff_qi", me)*100/query("max_qi", me)<10 )
                return notify_fail("你內傷太重，無法激勵易筋經至高絕學。\n");

        if( query("neili", me)<skill*5 || 
            query("max_neili", me)<500 )
                return notify_fail("你的真氣不夠。\n");

        addn("neili", -skill*5, me);
        me->receive_damage("qi", 0);

        message_combatd(HIM "$N" HIM "默念易筋經的口訣: "
                            "元氣,氣存于內,放于外。"
                            "易筋,孕懷于息,舒于支....\n"
                        HIW "一股詳和的白色罡氣自頭頂迅速"
                        HIW "遊遍" HIW "$N" HIW "的奇經八脈！\n"
                        HIR "你的內傷剎那間大為好轉！！\n" NOR, me);

        addn("max_neili", -skill/5, me);

        addn("eff_qi", skill*5, me);
        if( query("eff_qi", me)>query("max_qi", me) )
                set("eff_qi",query("max_qi",  me), me);
        set("qi",query("eff_qi",  me), me);

        if (me->is_fighting()) me->start_busy(5+random(5));

        return 1;
}