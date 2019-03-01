// train.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob,where;
        mapping fam;
        int sp, dp;
        int i, cost, train_level;

        seteuid(getuid());

        if (me->query_skill("training", 1) < 10)
                return notify_fail("你的馭獸術還不純熟，無法訓練野獸！\n");

        if (! arg)
                return notify_fail("你要訓練什麼野獸？\n");

        if (! objectp(ob = present(arg, environment(me))))
                return notify_fail("這裡沒有這只野獸吧？\n");

        if (playerp(ob)) 
                return notify_fail("人家也是玩家，你搞什麼搞啊？\n");

        if( query("race", ob) != "野獸" )
                return notify_fail("這不是野獸，你暈頭了吧？\n");

        if( query_temp("owner", ob) && 
            (query_temp("owner", ob) == query("id", me)) )
                return notify_fail(ob->name() + "就是你馴服過的，你還折騰個啥勁兒呢！\n");

        if( query_temp("owner", ob) && 
            (query_temp("owner", ob) != me) )
                return notify_fail(ob->name() + "早被人家馴服了，你還折騰個啥勁兒呢！\n");

        if (ob == me)
                return notify_fail("你沒這麼笨吧，把自己不當人？\n");

        if (! living(ob)) 
                return notify_fail("這只野獸暈倒了，你怎能訓得它動呢？\n");

        if (me->is_busy())
                return notify_fail("你正忙，等會兒再說吧。\n");

        cost=query("max_jing", me)/(me->query_skill("training",1)/10)-10;
        if( cost < 1 ) cost = 1;

        if( query("jing", me) <= cost )
                return notify_fail("現在你太累了，無法訓練野獸。\n");

        message_vision("只見$N沖著" + ob->name() +
                       "手腳亂擺，口中似對它輕輕細語。\n\n",me);

        sp=me->query_skill("training",1)+query("int", me);
        dp=query("combat_exp", ob)/100;
        
        if (random(sp) < random(dp) / 2)
        {
                ob->kill_ob(me);
                me->start_busy(1);
                return notify_fail("你馭獸術不精，那東西野"
                                   "性不泯，沖著你就竄了過來！\n");
        }

        me->receive_damage("jing", cost);
        message_vision("頓時" + ob->name() + "沖著$N搖了搖尾巴，很溫馴的樣子。\n\n", me);

        train_level = me->query_skill("training", 1);
        if (me->can_improve_skill("training"))
                me->improve_skill("training",random(query("int", me)));

        set("attitude", "peace", ob);
        ob->remove_all_enemy(1);
        set_temp("owner", me, ob);
        set_temp("owner_name",query("name",  me), ob);
        set_temp("owner_id",query("id",  me), ob);
        if( (strsrch(query("name", ob),"馬") >= 0) || 
            (strsrch(query("name", ob),"驢") >= 0) || 
            (strsrch(query("name", ob),"騾") >= 0) || 
            (strsrch(query("name", ob),"駝") >= 0) || 
            (strsrch(query("name", ob),"牛") >= 0) || 
            (strsrch(query("name", ob),"象") >= 0) || 
            (strsrch(query("name", ob),"獅") >= 0) || 
            (strsrch(query("name", ob),"虎") >= 0) || 
            (strsrch(query("name", ob),"豹") >= 0) || 
            (strsrch(query("name", ob),"鹿") >= 0) || 
            (strsrch(query("name", ob),"鯊") >= 0) || 
            (strsrch(query("name", ob),"雕") >= 0) )
                set("ridable", 1, ob);
        me->remove_all_enemy();
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : train <動物>

此指令可用于馴化某動物。對于已經馴服的動物，可以進行下述指令：

基本指令：
        come <動物名>:                  讓動物跟隨主人行動。
        stay:                           停止動物的跟隨狀態。
        attack <某人>:                  讓動物攻擊敵人。
        stop <動物名>:                  讓動物停止對人的攻擊。
        release:                        結束主奴狀態，將動物放離。

特殊指令：（只對某些動物適用）
        qi(ride) <動物名>:              騎，如騎馬，虎，雕，鯊等。
        xia(unride) <動物名>:           下，離開坐騎。
        wei(feed) <動物名>:             替動物喂食。
        yin <動物名>:                   給動物飲水。

HELP
        );
        return 1;
}
