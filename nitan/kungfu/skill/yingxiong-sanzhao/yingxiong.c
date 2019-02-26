// yingxiong.c

#include <ansi.h>
inherit F_SSERVER;

string name() { return "蓋世英雄"; }

int perform(object me, object target)
{
        int level;
        string msg;
        int ap, dp;

        if( !objectp(target) ) { target = offensive_target(me);}

        if( !target || !target->is_character() || target == me ||
            !me->is_fighting(target) ||
            !living(target) || query_temp("no_living", target) )
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query("gender", me) != "男性" && !wizardp(me) )
                return notify_fail("象你這副娘娘腔，也許練“絕世風姿”恐怕更合適點吧。\n");

        if( (int)me->query_skill("yingxiong-sanzhao", 1) < 150 )
                return notify_fail("你的英雄三招不夠嫻熟，不會使用"+name()+"。\n");

        if( (int)me->query_skill("force", 1) < 160 )
                return notify_fail("你的基本內功不夠嫻熟，不會使用"+name()+"。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的內力不足，恐怕沒法逞英雄了。\n");

        if( query_temp("shenlong/yingxiong", me) )
                return notify_fail("你已經在大擺英雄的譜了，還不夠啊？\n");

        level = me->query_skill("yingxiong-sanzhao", 1);
        addn("neili", -200, me);
        me->start_busy(1);

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");
        if( ap / 2 + random(ap) > dp )
        {
                message_combatd(HIY"$N"HIY"越鬥越是兇猛，激鬥中仰天大吼一聲：“蓋世英雄！！”，一股豪氣自$N心中升起，頓時更是兇悍起來。\n" NOR, me, target);
                set_temp("shenlong/yingxiong", 1, me);
                addn_temp("apply/attack", level, me);
                addn_temp("apply/unarmed_damage", level, me);
                if( !target->is_busy() )
                        target->start_busy(random(3)+1);
                me->start_call_out( (: call_other, __FILE__, "remove_effect", me, level:), 30);
        }
        else
        {
                message_combatd(HIG"激鬥中的$N衝着$n大喊：“蓋世。。。”，語意未了，就被$n迫得手忙腳亂。\n" NOR, me, target);
        }
        return 1;
}
void remove_effect(object me, int level)
{
        delete_temp("shenlong/yingxiong", me);
        addn_temp("apply/attack", -level, me);
        addn_temp("apply/unarmed_damage", -level, me);
        message_combatd(HIY"$N突然感到心底一陣失落：“歷代英雄，都歸孤冢。”一念及此，頓時意興蕭然。\n" NOR, me);
}

