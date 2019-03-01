// This program is a part of NITAN MudLIB
// youming.c  幽冥鬼影

#include <ansi.h>

inherit F_SSERVER;

string name() { return "幽冥鬼影"; }

int perform(object me, object target)
{
        int skill;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「幽冥鬼影」只能在戰鬥中使用。\n");

        if ((int)me->query_skill("youming-guizhao", 1) < 120 )
                return notify_fail("你的幽冥鬼爪等級不夠，不能呼喚鬼影！\n");

        if ((int)me->query_skill("claw", 1) < 120 )
                return notify_fail("你的基本爪法極不夠嫻熟，不能呼喚鬼影！\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手使用「幽冥鬼影」！\n");

        /*
        if ((int)me->query_skill("xiaowuxiang", 1)<100
                && (int)me->query_skill("bahuang-gong", 1)<100
                && (int)me->query_skill("beiming-shengong", 1)<100)
                return notify_fail("你的逍遙派內功火候不夠。\n");

        if (me->query_skill_mapped("force") != "xiaowuxiang"
                && me->query_skill_mapped("force") != "bahuang-gong"
                && me->query_skill_mapped("force") != "beiming-shengong")
                return notify_fail("你沒有運用逍遙派內功！\n");
        */

        if (me->query_skill_prepared("claw") != "youming-guizhao"
                || me->query_skill_mapped("claw") != "youming-guizhao"
                || me->query_skill_mapped("parry") != "youming-guizhao")
                return notify_fail("你現在無法呼喚出鬼影進行攻擊！\n");

        if( query("neili", me)<800 )
                return notify_fail("你現在真氣太弱，不能呼喚鬼影！\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你現在內力太弱，不能呼喚鬼影！\n");

        if( query_temp("lingjiu/youming", me) )
                return notify_fail("你已經呼喚出了幽冥鬼影！\n");

        skill = me->query_skill("claw");

        message_combatd(HIR "突然$N咬破舌尖，高聲叫喚天地鬼神，如同瘋子一般！跟著地面變得有如水動，只見\n"
                        "一條"HIB"鬼影"HIR"從地底冒出，飛于半空，身行飄渺不定，時而象一火球，時而象一黑影！\n\n" NOR,
                        me);

        addn("neili", -skill, me);
        set_temp("lingjiu/youming", 1, me);
        addn_temp("apply/defense", skill/2, me);

        call_out("checking", 1, me, target);
        call_out("remove_effect", skill/5+2, me);

        return 1;
}
void checking(object me, object target)
{
        int skill;
        skill = me->query_skill("claw");

        if( !living(me) || me->is_ghost() )
        {
                message_combatd(HIR"那條"HIB"鬼影"HIR"于半空徘徊了一陣，就消失在地底了！\n"NOR, me);
                addn_temp("apply/defense", -skill/2, me);
                delete_temp("lingjiu/youming", me);
                remove_call_out("remove_effect");
                return ;
        }
        if( !me->is_fighting() )
        {
                message_combatd(HIR"那條"HIB"鬼影"HIR"于半空徘徊了一陣，就消失在地底了！\n"NOR, me);
                addn_temp("apply/defense", -skill/2, me);
                delete_temp("lingjiu/youming", me);
                remove_call_out("remove_effect");
                return ;
        }
        if( me->query_skill_mapped("force") != "bahuang-gong"
           || me->query_skill_mapped("claw") != "youming-guizhao"
           || me->query_skill_prepared("claw") != "youming-guizhao" )
        {
                tell_object(me,"\n$N驟然變換招數，不能再繼續用幽冥鬼影牽制對手的攻擊！\n");
                addn_temp("apply/defense", -skill/2, me);
                message_combatd(HIR"那條"HIB"鬼影"HIR"于半空徘徊了一陣，就消失在地底了！\n"NOR, me);
                delete_temp("lingjiu/youming", me);
                remove_call_out("remove_effect");
                return ;
        }
        else
                call_out("checking", 1, me, target);
        return;
}
void remove_effect(object me)
{
        int skill;

        if (! me) return;

        skill = me->query_skill("claw");

        message_combatd(HIR"地面的波動漸漸減弱，那條"HIB"鬼影"HIR"于半空徘徊了一陣，就消失在地底了！\n"NOR, me);
        addn_temp("apply/defense", -skill/2, me);
        delete_temp("lingjiu/youming", me);
        return;
}
