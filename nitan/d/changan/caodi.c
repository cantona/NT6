// This program is a part of NT MudLIB
#include <ansi.h>

inherit ROOM;
void create()
{
        set("short", "草地");
        set("long",@LONG
這是一片空曠的草地，四周長滿了雜草，似乎這裡已經很久沒有
人來過了，面對這曠野的地方，你的心中不由得升起一絲寒意。再往
東走就是一個深不見底的絕崖了。
LONG
);
        set("outdoors","changan");
        set("exits", ([
                "west" :__DIR__"boshulin10",
                "east" :__DIR__"jueya",
        ]));
        set("item_desc", ([
                "草地" : "在這片草地的中間，你似乎感到一些異樣。\n",
        ]));
        set("coor/x", -10620);
	set("coor/y", 1980);
	set("coor/z", 0);
	setup();
}

void init()
{
        if (interactive(this_player()))
                add_action("do_kill","kill");
}

void check(object me,object ob)
{
        if (!me || !ob)
                return;

        if (!present(me,this_object())
        ||  !present(ob,this_object()))
                return;

        if( query("jiali", ob) != (ob->query_skill("force")/2 )
         || query("jiali", me) != (me->query_skill("force")/2) )
                return;

        if( query("max_neili", me)<100000
         || query("max_neili", ob)<100000 )
                return;

        if( query("max_neili", ob)<query("max_neili", me) )
        {
                message_vision("$n被$N內力一震，往崖邊倒飛下去。\n",me,ob);
                ob->move(__DIR__"qinhuang/gudi.c");
                set_temp("killer", 1, ob);
                ob->unconcious();
        }
        else
        {
                message_vision("$N被$n內力一震，往崖邊倒飛下去。\n",me,ob);
                me->move(__DIR__"qinhuang/gudi.c");
                set_temp("killer", 1, me);
                me->unconcious();
        }
}

int do_kill(string arg)
{
        object ob, me=this_player();

        if (!arg || arg=="")   return 0;
        if (ob=present(arg, this_object()))
        {
                message_vision( HIY "$N和$n一見面，立即廝殺了起來。\n" NOR ,me,ob);
                if (userp(ob) &&
                    query("jiali", ob) == (ob->query_skill("force")/2) && 
                    query("jiali", me) == (me->query_skill("force")/2) )
                {
                        remove_call_out("check");
                        call_out("check",random(20)+5,me,ob);
                }
        }
        return 0;
}

