// Room: /d/guiyun/shushang.c
// Last Modified by winder on Jul. 9 2001

#include <ansi.h>
#define DOWN_TREE __DIR__"shulin5"
inherit ROOM;

int do_kill(string arg);
int do_climb(string arg);
string look_down();

void create()
{
        set("short", "樹上");
        set("long",@LONG
這裏是大樹的樹頂。往周圍看，四面都是樹，往下看，枝葉繁盛，
透過樹葉的空隙，你能約略看到樹下(down)的情景。
LONG
);
/*        set("exits",([
                "down" : __DIR__"shulin5",
        ]) );*/
        set("item_desc", ([
                "down" : (: look_down :),
        ]) );

        set("no_clean_up",0);
        set("outdoors", "guiyun");
        setup();
}

void init()
{
        object room, *ob;
        object here = this_object();
        object me = this_player();
        int i;

        if (userp(me) && !wizardp(me))
        {
                if (!room = find_object(DOWN_TREE)) 
                        room = load_object(DOWN_TREE);
                ob = all_inventory(here);
                for (i = 0; i < sizeof(ob); i++)
                {
                        if (userp(ob[i]) && !wizardp(ob[i]) && ob[i] != me)
                        {
                                write("沒想到" + ob[i]->name() + "也藏在樹上！\n");
                                message_vision("因為樹枝無法承受兩個人的重量，“啪”地一聲折斷了！\n", me);
                                me->move(DOWN_TREE, 1);
                                ob[i]->move(DOWN_TREE, 1);
                                message_vision("只聽“唏哩嘩啦”一陣亂響，$N和$n從樹上掉了下來。\n", me, ob[i]);
                                message_vision("$N大怒，衝$n嚷道：“" + RANK_D->query_self_rude(ob[i]) + "在上面呆的好好的，你個" + RANK_D->query_rude(me) + "幹嘛來搗亂？”\n", ob[i], me);
                                message_vision("$N也不服氣地反駁道：“你躲在上面，一看就知道不是好人！”\n", me);
                                message_vision("兩人越説越僵，終於拳腳相加！\n", me);
                                me->fight_ob(ob[i]);
                                ob[i]->fight_ob(me);
                                return;
                        }
                }
        }
        "/cmds/std/look"->look_room(me, here);
        add_action("do_kill", "kill");
        add_action("do_kill", "sha");
        add_action("do_kill", "touxi");
        add_action("do_climb", "climb");
        add_action("do_climb", "pa");
}

string look_down()
{
        object down;

        if (!down = find_object(DOWN_TREE))
                down = load_object(DOWN_TREE);
        "/cmds/std/look"->look_room(this_player(), down);
        return "";
}

int do_climb(string arg)
{
        object me = this_player();

        if (arg != "down")
                return notify_fail("你要爬到哪裏？\n");
        message_vision("$N順着樹幹爬了下去。\n", me);
        me->move(DOWN_TREE);
        message("vision", me->name() + "從樹上爬了下來。\n", DOWN_TREE, ({me}));
        return 1;
}

int do_kill(string arg)
{
        object room, ob;
        object me = this_player();
//        int temp;
        string callname;

        if (me->is_busy())
                return notify_fail("你正忙着哪！\n");

        if (!arg || !(room = find_object(DOWN_TREE)))
                return notify_fail("你要偷襲誰？\n");

        if (!(ob = present(arg, room)))
                return notify_fail("你要偷襲誰？\n");

        if (!ob->is_character() || ob->is_corpse())
                return notify_fail("看清楚一點，那並不是活物。\n");

        if (!userp(ob)) {
                write("偷襲NPC？你想作弊啊！\n");
                return 1;
        }

        if (wiz_level(me) < wiz_level(ob))
                return notify_fail("你不能攻擊巫師等級比你高的對手。\n");

        message("vision", me->name() + "一躍而下，向樹下的" + ob->name() + "發起了偷襲！\n", this_object(), ({me}));
        me->move(room, 1);
//        temp = me->query("dex") / 10 + 1;
        if (random(4))
        {
                message_vision("$N從樹上急躍而下，和身撲向$n，$n錯愕間竟然驚呆了！\n", me, ob);
                ob->start_busy(3);
        }
        else {
                message_vision("$N從樹上急躍而下，看來是想偷襲$n，卻在落地時不小心跌了一跤，$n趁機立刻發動攻擊！\n", me, ob);
                me->start_busy(5);
        }
        if( userp(me) && userp(ob) && query("combat_exp", ob)<1000 )
                return notify_fail("你的心腸太黑了, 對手無縛雞之力的玩家也下得了手。\n");
        callname = RANK_D->query_rude(ob);

        message_vision("\n$N對着$n喝道：「" + callname + "！今日不是你死就是我活！」\n\n", me, ob);

        delete_temp("guarding", me);
        set_temp("guarding", 1, ob);
        me->kill_ob(ob);
        if( !userp(ob) )
                ob->kill_ob(me);
        else {
                ob->fight_ob(me);
                if (userp(me))
                        tell_object(ob, HIR "如果你要和" + me->name()
                        + "性命相搏，請你也對這個人下一次 kill 指令。\n" NOR);
        }
        return 1;
}