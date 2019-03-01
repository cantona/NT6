// taiyi2.c
// Java Oct.10 1998
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "太乙池");
        set("long", @LONG
你身在湖水裡，只覺得湖水冰涼透骨。但見四周高峰環列，池面
碧波盪漾，山光水影，風景貽人。這裡原來是太乙池的東岸，太累的
話，你可以爬(climb) 上岸。遠遠望去，西邊的山峰之間似乎有一個
大洞。想不想遊(swim)過去看？
LONG
        );
        set("outdoors", "zhongnan");
        set("coor/x", -3190);
        set("coor/y", 180);
        set("coor/z", 40);
        setup();
}
void init()
{
        add_action("do_climb", "climb");
        add_action("do_swim", "swim");
}
int do_climb(string arg)
{
        object me = this_player(); 
        int c_exp;
        c_exp=query("combat_exp", me);
        if( !arg || arg != "up")
        {
                write("那個方向沒法爬。\n");
                return 1;
        }

        message_vision("$N在太乙池中往岸上爬了上去。\n", me);
        me->move("/d/quanzhen/taiyi1");
        message_vision("$N從太乙池中爬了上去。\n", me);
        return 1;
}
int do_swim()
{
        int c_exp,c_skill;
        object me = this_player();

        c_exp=query("combat_exp", me);
        c_skill=me->query_skill("jinyan-gong",1);
        if( query("qi", me)<10 )
                me->unconcious();
        else
        {
                me->receive_damage("qi",10);
                if (((c_skill*c_skill*c_skill/10)< c_exp) && (c_skill < 51))
                        me->improve_skill("jinyan-gong", (int)me->query_skill("jinyan-gong", 1));
                message_vision("$N在太乙池中劃了劃水，用力遊了起來。\n", me);
        }
        return 1;
}