#include <ansi.h>
inherit ROOM; 
void create()
{
        int i;
        set("short", "書架頂");
        set("long", @LONG
書架頂上積滿了厚厚的一層灰塵，書架頂和房樑還有三尺多高的
距離由于不經常打掃，這裡步滿了蜘蛛絲，書架頂的浮塵上還能依稀
見到一些爬蟲留下的痕跡有時候有些小鳥也會在這裡築巢。
LONG );
        set("exits", ([ /* sizeof() == 1 */
                "down" : "/d/shaolin/cjlou1",
        ]));        

        set("bamboo_count", 1);
        // set("yijinjing_count", 1);
        setup();
}

void init()
{ 
        add_action("do_pull", "qingsao");
        add_action("do_pull", "clear");
}

int do_pull()
{
        object ob, *obs, me = this_player();
        
        if (me->is_busy())
                return notify_fail("你正忙著呢！\n");
                
        message_vision("$N仔細地打掃了書架頂上的灰塵,看上去幹凈多了。\n", me);
        me->start_busy(5);
        
        // obs = filter_array(children("/clone/book/yijinjing.c"), (: clonep :));
        // if (query("bamboo_count") > 0 && sizeof(obs) < 3) 
        if (query("bamboo_count") > 0)
        {
                    ob = new("/clone/book/yijin_book"); 
                ob->move(me, 1);
                addn("bamboo_count", -1);
                CHANNEL_D->do_channel(this_object(),"rumor",sprintf("%s搞到了少林鎮寺之寶易筋經秘籍啦。",query("name", me)));
        } else
        if (query("yijinjing_count") > 0)
        {
                if (random(2)) ob = new("/clone/book/yjj_book2");
                else ob = new("/clone/book/yijinjing");
                ob->move(me, 1);
                addn("yijinjing_count", -1);
                CHANNEL_D->do_channel(this_object(),"rumor",sprintf("%s搞到了少林鎮寺之寶易筋經殘譜啦。",query("name", me)));
        }
        return 1;
}

void reset()
{
        set("bamboo_count", 1);
        // set("yijinjing_count", 1);
}
