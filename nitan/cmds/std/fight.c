// fight.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object obj, old_target;

        if (me->is_chatter())
                return 0;

        if( query("no_fight", environment(me)) )
                return notify_fail("這裡禁止戰鬥。\n");

        if( !arg
        ||  !objectp(obj = present(arg, environment(me)))
        ||  !me->visible(obj) )
                return notify_fail("你想攻擊誰？\n");

        if (! obj->is_character())
                return notify_fail("看清楚一點，那並不是生物。\n");

        if (obj->is_fighting(me))
                return notify_fail("加油！加油！加油！\n");

        if (! living(obj))
                return notify_fail(obj->name() + "已經無法戰鬥了。\n");

        if( query("qi", me)<query("max_qi", me)*3/10 )
                return notify_fail("你現在沒有力氣戰鬥了。\n");

        if (obj == me) return notify_fail("你不能攻擊自己。\n");

        if( query("can_speak", obj) )
        {
                message_vision("\n$N對著$n說道："
                        + RANK_D->query_self(me)
                        + me->name() + "，領教"
                        + RANK_D->query_respect(obj) + "的高招！\n\n", me, obj);

                if( objectp(old_target=query_temp("pending/fight", me)) )
                        tell_object(old_target, YEL + me->name() + "取消了和你比試的念頭。\n" NOR);
                set_temp("pending/fight", obj, me);

                notify_fail("看起來" + obj->name() + "並不想跟你較量。\n");
                switch (obj->accept_fight(me))
                {
                case 0:
                        return userp(obj);
                case -1:
                        return 1;
                default:
                }

                me->fight_ob(obj);
                obj->fight_ob(me);
        } else
        {
                message_vision("\n$N大喝一聲，開始對$n發動攻擊！\n\n", me, obj);
                me->fight_ob(obj);
                obj->kill_ob(me);
        }

        return 1;
}
int help(object me)
{
        write(@HELP
指令格式 : fight <人物>

這個指令讓你向一個人物「討教」或者是「切磋武藝」，這種形式的戰鬥純粹是
點到為止，因此只會消耗體力，不會真的受傷，但是並不是所有的  NPC 都喜歡
打架，因此有需多狀況你的比武要求會被拒絕。

其他相關指令: kill

PS. 如果對方不願意接受你的挑戰，你仍然可以逕行用 kill 指令開始戰鬥，有
    關 fight 跟 kill 的區分請看 'help combat'.
HELP );
        return 1;
}