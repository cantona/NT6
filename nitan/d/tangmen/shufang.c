//shufang.c  by winder

#include <room.h>
#include <skill.h>

inherit ROOM;

void create()
{        
        seteuid(getuid());
        set("short", "書房");
        set("long",
"這是蓮藕小築裡的書房。唐門弟子可以在這裡研學詩畫。靠牆並排擺\n"
"著幾個書架，一本唐詩選集(shi)引起了你的注意，另外牆上還掛了幾幅\n"
"字畫(hua)，看來在這裡可以學到不少東西。\n"
);        
        set("exits", ([        
                "east" : __DIR__"nzlangw3",
        ]));
        set("item_desc", ([
                "shi" : "這是一本很平常的唐詩選集。不少弟子在吟頌(yin)。\n",
                "hua" : "這是一幅臨摹鄭板橋的字畫。不少弟子在看(kan)。\n",
        ]));

        set("no_steal", "1");
        set("no_fight", "1");
        set("area", "tangmen");
        set("objects", ([
                CLASS_D("tangmen") + "/tangyu" : 1,
        ]));

        setup();
}

void init()
{
        add_action("do_look","kan");
        add_action("do_du","yin");
}

int do_look(string arg)
{
        object me;
        int cost;

        me = this_player();
        cost = 10 + ( 20 - (int)me->query_int() ) / 2;

        if ( cost < 1) cost = 0;

        if ( me->is_busy() )
                return notify_fail("你現在正忙著呢。\n");

        if ( arg == "hua")
        {
                if( (int)me->query_skill("literate", 1) > 50 )
                        return notify_fail("你對著字畫仔細揣摩了一會兒，發現從中已經學不到什麼了。\n");

                if( query("jing", me)>cost && 
                    query("potential", me)-query("learned_points", me) >= 1 )
                {
                        tell_object(me, "你專心地研讀牆上的字畫，不時還伸出手指臨摹一番。\n");
                        me->improve_skill("literate", random( (int)me->query_skill("literate", 1) / 2 ) + 10 );
                        me->receive_damage("jing", cost );
                        addn("potential", -1, me);
                }
                else
                {
                        if( query("jing", me) <= cost )
                                write("你現在過于疲倦，無法專心下來研讀新知。\n");

                        if( query("potential", me)-query("learned_points", me) <= 0 )
                                write("你看著字畫反復琢磨，竟沒有一絲心得。\n");
                }
                return 1;
        }
        else
                return 0;
}

int do_du(string arg)
{
        object me;
        int cost;

        me = this_player();
        cost = 10 + ( 30 - (int)me->query_int() ) / 2;

        if ( cost < 1) cost = 0;

        if ( me->is_busy() )
                return notify_fail("你現在正忙著呢。\n");

        if ( arg == "shi")
        {
                if( (int)me->query_skill("literate", 1) < 51 )
                        return notify_fail("你拿起唐詩選集，翻開一頁發現竟什麼也看不懂。\n");

                if( (int)me->query_skill("literate", 1) > 101 )
                        return notify_fail("你拿起唐詩選集，翻了翻發現沒有什麼可學的了。\n");

                if( query("jing", me)>cost && 
                    query("potential", me)-query("learned_points", me) >= 1 )
                {
                        tell_object(me, "你專心地研讀書架上的詩集，讀到忘情時竟讀出了聲。\n");
                        me->improve_skill("literate", random( (int)me->query_skill("literate", 1) / 2 ) + 20 );
                        me->receive_damage("jing", cost );
                        addn("potential", -1, me);

                }
                else
                {
                        if( query("jing", me) <= cost )
                                write("你現在過于疲倦，無法專心下來研讀新知。\n");

                        if( query("potential", me) <= query("learned_points", me) )
                                write("你看著詩集反復琢磨，竟沒有一絲心得。\n");
                }
                return 1;
        }
        else
                return 0;
}