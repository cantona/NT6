// ting.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me)
{
        object ob;

        seteuid(getuid());

        if( !query_temp("comedby", me) )
                return notify_fail("已經沒有野獸跟着你了！\n");
        if( me->is_fighting() )
                return notify_fail("一邊打架一邊馴獸？你真是活膩了！\n");
        if( !objectp(ob=present(query_temp("comedby", me),environment(me))) )
                return notify_fail("這裏沒有這隻野獸吧？\n");
        if( !query_temp("owner", ob) )
                return notify_fail(ob->name() + "是隻無主野獸，你得先馴服(train)它啊！\n");
        if( query_temp("owner", ob) && 
           (query_temp("owner", ob) != query("id", me)) )
        {
                ob->kill_ob(me);
                return notify_fail(ob->name() + "是被人家馴服了，你不是找死啊！\n");
        }
        if ( ob == me )
                return notify_fail("你沒問題吧，自己跟自己？\n");
        if (!living(ob)) 
                return notify_fail("這隻野獸暈倒了，你怎能讓它跟你呢？\n");
        if (ob->is_fighting()) 
                return notify_fail("它正在大打出手，沒空理你呢？\n");

        message_vision("只見$N衝着"+ob->name()+"手中擺了個手式，它衝着你點了點頭。\n\n",me);

        delete_temp("comedby", me);
        ob->set_leader(0);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : stay <動物>

此指令可用於讓某動物停止跟隨你。對於已經馴服的動物，可以進行下述指令：

基本指令：
        come <動物名>:                  讓動物跟隨主人行動。
        stay:                           停止動物的跟隨狀態。
        attack <某人>:                  讓動物攻擊敵人。
        stop <動物名>:                  讓動物停止對人的攻擊。
        release:                        結束主奴狀態，將動物放離。

特殊指令：（只對某些動物適用）
        qi(ride) <動物名>:              騎，如騎馬，虎，雕，鯊等。
        xia(unride) <動物名>:           下，離開坐騎。
        wei(feed) <動物名>:             替動物餵食。
        yin <動物名>:                   給動物飲水。

HELP
        );
        return 1;
}
