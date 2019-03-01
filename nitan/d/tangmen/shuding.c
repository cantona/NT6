//shuding.c  by winder

#include <room.h>
#include <skill.h>
#include <ansi.h>

inherit ROOM;

void create()
{        
        seteuid(getuid());
        set("short", "樹頂");
        set("long",
"這是萬年古鬆的樹頂。當年祖師爺？？？曾在這裡日觀雲動，夜觀星\n"
"變，最終悟出了？？？？的唐門絕學，因此很多弟子常常在這裡日夜靜坐。\n"
);        
        set("item_desc", ([
                "down" : "一眼望去只見白雲片片，猶如棉絮般輕柔，隨著山風飄來飄去。\n",
        ]));

        set("area", "tangmen");
        setup();
}

void init()
{
        add_action("do_wu","lingwu");
        add_action("do_climb","climb");
        add_action("do_climb","pa");
}

int do_wu(string arg)
{
        object me;
        int cost;
        int c_exp;
        int d_skill, f_skill;

        me = this_player();
        cost=20+(30-query("int", me))/2;//原始值為15+。加大點難度
        c_exp=query("combat_exp", me);
        d_skill = (int)me->query_skill("dodge",1); 
        f_skill = (int)me->query_skill("finger",1); 

        if ( cost < 1)
                cost = 0;

        if ( 25 - (int)me->query_int() > 0 )
             return notify_fail("以你目前的悟性，恐怕不會領悟到什麼。\n");

        if( !me->query_skill("literate", 1) )
                return notify_fail("你是個文盲，先學點文化(literate)吧。\n");

        if ( me->is_busy() )
                return notify_fail("你現在正忙著呢。\n");

        if( me->is_fighting() )
                return notify_fail("你無法在戰鬥中靜心領悟！\n");
        if ( arg == "yun")
        {
                if( (int)me->query_skill("dodge", 1) < 51 )
                        return notify_fail("你日觀雲變，但是卻無法從中領悟什麼。\n");

                if( (int)me->query_skill("dodge", 1) > 201 )
                        return notify_fail("你日觀雲變，自覺一切變化都已熟記于心。\n");

                if( d_skill*d_skill*d_skill/10 > c_exp )
                                      return notify_fail("你靜觀天變，但由于實戰經驗不足沒有領悟到什麼。\n"); 

                if( query("jingli", me)>cost )
                {
                        tell_object(me, "你盤膝坐下靜觀頭頂浮雲隨風飄動，毫無蹤跡可尋。\n你對基本身法有了進一步認識。\n");
                        me->improve_skill("dodge", random( (int)me->query_skill("literate", 1) / 2 ) + 20 );
                        addn("jingli", -cost, me);
                }
                else
                {
                        if( query("jingli", me) <= cost )
                                write("你現在過于疲倦，無法靜下心來領悟。\n");
                }
                return 1;
        }
        else
                if ( arg == "xing")
                {
                        if( (int)me->query_skill("finger", 1) < 51 )
                                return notify_fail("你夜觀星變，但是卻無法從中領悟什麼。\n");
        
                        if( (int)me->query_skill("finger", 1) > 201 )
                                return notify_fail("你夜觀星變，自覺一切變化都已熟記于心。\n");

                        if( f_skill*d_skill*d_skill/10 > c_exp )
                                      return notify_fail("你靜觀天變，但由于實戰經驗不足沒有領悟到什麼。\n"); 
        
                        if( query("jingli", me)>cost )
                        {
                                tell_object(me, "你盤膝坐下靜觀頭頂明星閃爍，忽靜忽動。\n你對基本手法有了進一步認識。\n");
                                me->improve_skill("finger", random( (int)me->query_skill("literate", 1) / 2 ) + 20 );
                                addn("jingli", -cost, me);
                        }
                        else
                        {
                                if( query("jingli", me) <= cost )
                                        write("你現在過于疲倦，無法靜下心來領悟。\n");
                        }
                        return 1;
                }
                else
                        return 0;
}

int do_climb(string arg)
{
        object ob;
        ob = this_player();

        if ( arg && arg == "down" )
        {
                message_vision(HIC "$N攀著繁茂的樹枝一步步爬了下去。\n" NOR, ob);
                ob->move(__DIR__"shugan3");
                return 1;
        }
        else
                return notify_fail("你要向哪裡爬？\n");
}