// touxi.c 偷襲
// by King 97.05

#include <ansi.h>

int main(object me, string arg)
{
        object obj;
        int skill, count;

        if( query("no_fight", environment(me)) )
                return notify_fail("這裏禁止戰鬥。\n");

        if (! arg || !objectp(obj = present(arg, environment(me))) || !me->visible(obj) )
                return notify_fail("你想偷襲誰？\n");

        if (me->is_chatter())
                return notify_fail("你這個樣子有什麼好偷襲的？\n");

        if (! obj->is_character())
                return notify_fail("看清楚一點，那並不是生物。\n");

        if (obj->is_fighting(me))
                return notify_fail("你已經在戰鬥中了，還想偷襲？\n");

        if (! living(obj))
                return notify_fail(obj->name() + "都已經這樣了，你還用"
                                   "得着偷襲嗎？\n"); 

        if (obj == me)
                return notify_fail("偷襲自己？別這麼想不開。\n");

        if (me->is_busy())
                return notify_fail("你的動作還沒有完成，不能偷襲。\n");

        if (obj->query_competitor())
                return notify_fail("人家比武你要偷襲？真是太不要臉了。\n");

        tell_object(me, "你飛身縱起，撲向" + obj->name() +"！\n\n");
        tell_object(obj, CYN + me->name() + "忽然向你撲來！\n\n" NOR);
        message("vision", CYN + me->name() + "忽然向" + obj->name() +
                          "撲去！\n\n" NOR, environment(me), ({me, obj}));

        switch (obj->accept_touxi(me))
        {
        case 0:
                return 0;
        case -1:
                return 1;
        }

        count = me->query_str();

/*
        if( query("id", userp(me) && userp(obj) && !obj->is_want_kill(me)) )
                me->want_kill(obj);
        me->kill_ob(obj);
*/

        if( random(query("combat_exp", me))<query("combat_exp", obj)/2 )
        {
                addn_temp("str", count*4, me);
                COMBAT_D->do_attack(me,obj,query_temp("weapon", me));
                addn_temp("str", -count*4, me);
        } else
        {
                COMBAT_D->do_attack(me,obj,query_temp("weapon", me));
                COMBAT_D->do_attack(me,obj,query_temp("weapon", me));
                COMBAT_D->do_attack(me,obj,query_temp("weapon", me));
        }

   //me->start_busy(3);
        obj->kill_ob(me);

        return 1;
}

int help(object me)
{
  write(@HELP
指令格式 : touxi <人物>
 
這個指令用來向敵人偷襲。偷襲不成時，則會招至反擊。特別適合於
經驗低的玩家向經驗高的玩家拚命。:)

其他相關指令: fight, kill, hit
HELP
    );
    return 1;
}