// chaoyang.c

inherit ROOM;
#include <ansi.h>
 
void create()
{
        set("short", "朝陽峯");
        set("long", @LONG
這裏就是華山的東峯，也稱朝陽峯，是華山看日出的絕佳處。於
此俯瞰，黃河隱顯東迤如帶，南望小孤峯背倚山河。小孤峯上有一小
亭，覆以鐵瓦，亭中擺有鐵棋盤一局，那就是華山著名的『博台』了。
遠望東壁懸崖（ya）上，更有一個巨型掌印，相傳為「河神巨靈」劈
山時所留下的，李白詩中『巨靈咆哮劈兩山，洪波噴流射東海』就是
指這個上古傳説。
LONG );
        set("exits", ([ /* sizeof() == 1 */
                "westdown" : __DIR__"chaopath2",
        ]));


        set("item_desc", ([
                "ya"   : NOR + WHT "懸崖下峭壁高聳，一條青藤（teng）直垂而下。\n" NOR,
                "teng" : HIG "一根青藤，拉（la）住它可做攀爬之用。\n" NOR,
        ]));

        set("outdoors", "huashan" );
        
        set("tian_count", 1);

        setup();
}
 
void init()
{
        add_action("do_la", "la");
        add_action("do_jump", "jump");
        add_action("do_shout", "shout");
        add_action("do_shout", "hu");
        add_action("do_shout", "jiao");        
}

int do_la(string arg)
{
        object me = this_player();

        if (! arg || arg != "teng")
               return notify_fail("你要拉什麼？\n");

        if (me->is_busy() || me->is_fighting())
               return notify_fail("等你忙完了再説吧！\n");

        if( query_temp("la_teng_huashan", me) )
               return notify_fail("你已經拉住青藤了。\n");

        message_vision(HIG "$N" HIG "將青藤牢牢地抓住了。\n", me);

        set_temp("la_teng_huashan", 1, me);

        me->start_busy(2);

        return 1;          
}

int do_jump(string arg)
{
        object me = this_player();

        if (! arg || arg != "ya")
               return notify_fail("你要往哪兒跳？\n");

        if (me->is_busy() || me->is_fighting())
               return notify_fail("等你忙完了再説吧！\n");

        if( !query_temp("la_teng_huashan", me) )
        {

               message_vision(HIM "$N" HIM "縱身跳下懸崖 ……\n", me);

               CHANNEL_D->do_channel(this_object(), "rumor", "聽説" + me->name() + HIM "跳"
                                     "下華山懸崖，自殺生亡。\n" NOR); 

               me->die();               
               return 1;

        }

        message_vision(HIG "$N" HIG "拉着青藤跳下懸崖……\n", me);
                
        tell_object(me, HIG "猛然間，你發現下面有一個小洞，你猛一彎腰，借力跳了進去。\n" NOR);

        me->move("/d/huashan/jinshedong");

        me->start_busy(2);

        return 1;          
}

int do_shout(string arg)
{
        object ob, me = this_player();

        if (! arg || arg == "") return 0;

        message_vision("$N高聲叫道：" + arg + "。\n", me);

        if ((arg == "風清揚前輩" || arg == "風前輩" || arg == "風老前輩") 
         && query("tian_count") >= 1 && query_temp("marks/風", me) == 1
        &&  ! present("tian boguang", environment(me))) 
        {
                addn("call_times", 1);

                if ((int)query("call_times") == 3) 
                {
                        message_vision("只聽得身旁的樹上傳來一陣嘮騷：誰要找風老前輩啊？\n", me);
                        message_vision("接着一個微醉的大漢從樹上爬了下來，盯着你看了一會兒。\n", me);
                        addn("tian_count", -1);
                        ob = new(__DIR__"npc/boguang.c");
                        ob->move(environment(me));
                        delete("call_times");
                }

        }
        return 1;
}

void reset()
{
        set("tian_count", 1);
        ::reset();
}