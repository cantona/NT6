// hit.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object obj, old_target;

        if( me->is_chatter() )
                return 0;

        if( query("no_fight", environment(me)) )
                return notify_fail("這裏禁止戰鬥。\n");

        if( !arg || !objectp(obj = present(arg, environment(me))) )
                return notify_fail("你想攻擊誰？\n");

        if( !obj->is_character() )
                return notify_fail("看清楚一點，那並不是你能招呼的對象。\n");

        if( query_temp("apply/name", me) && playerp(obj) )
                return notify_fail("你還是先取下面具吧!\n");

        if( !living(obj) )
                return notify_fail("你還要打？不如殺了算了。\n");

        if( obj->is_fighting(me) )
                return notify_fail("加油！加油！加油！\n");

        if( obj == me)
                return notify_fail("打自己？別這麼想不開。\n");

        if( query("age", obj) <= 17 && userp(obj) )
                return notify_fail("為了世界更美好，放過小孩子吧.\n");

        if( query("qi", me)<query("max_qi", me)*3/10 )
                return notify_fail("你現在沒有力氣戰鬥了。\n");

        if( query("can_speak", obj) )
                message_vision("\n$N對著$n大喝一聲：看招！\n\n", me, obj);
        else
                message_vision("\n$N大喝一聲，開始對$n發動攻擊！\n\n", me, obj);

        notify_fail("你無從下手。\n");
        switch( obj->accept_hit(me) )
        {
        case 0:
                return 0;
        case -1:
                return 1;
        default:
        }

        me->fight_ob(obj);
        if( query("can_speak", obj)){
                if( userp(obj) ) {
                        if( query("age", me)<18 )
                                me->want_kill(obj);
                        obj->fight_ob(me);
                        remove_call_out("do_hit");
                        call_out("do_hit", 1, me, obj);
                } else {
                        if( query("shen", obj)<-3000 )
                                obj->kill_ob(me);
                        else
                                obj->fight_ob(me);
                }
        } else
                obj->kill_ob(me);

        return 1;
}

void do_hit(object me, object obj)
{
        if( objectp(present(obj, environment(me))) ) {
                COMBAT_D->do_attack(me,obj,query_temp("weapon", me));
                COMBAT_D->do_attack(obj,me,query_temp("weapon", obj));
        }
        return;
}

int help(object me)
{
        write(@HELP
指令格式 : hit <人物>

這個指令讓你直接向一個人物「進招」。這種形式的戰鬥是即時的，只要玩家一
敲這個命令，戰鬥就會開始，直到某一方受傷50% 以上為止。這個指令對那些不
喜歡fight的NPC很有用，因為很多時候你的比武要求會被拒絕。不過使用這個命
令有可能遭到NPC 的強烈反應，所以要小心使用。

其他相關指令: fight, kill

HELP );
        return 1;
}

