#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", GRN "【青龍洞】" NOR);
        set("long", GRN @LONG

                    青         龍         洞

    這裏是陰司碧水寒潭最深處的一個洞穴，洞的上部空曠，存有少量
的空氣，你終於可以換氣了。傳説四神獸之首的青龍就棲息於此地。洞
內幽暗無比，令你根本看不清周圍的事物，很難追尋(xun) 到青龍的蹤
影。潭水冰冷刺骨，令人難以忍受，你只覺得氣力在一點一點消失。洞
穴深處有一股凜冽的寒流形成了一個急速流動的旋渦(xuanwo)。

LONG NOR );

        set("objects", ([
                __DIR__"obj/shuizao" : 1,
        ]));
        if (random(5) == 1)
                add("objects", ([ __DIR__"npc/yin2" : 1,]));

        set("item_desc", ([
                "xuanwo" : HIW "\n一股由寒流形成的旋渦，你似乎"
                           "可以通過它回到地面。\n" NOR,
        ]));

        set("qinglong", 1);
        set("no_magic", 1);
        set("is_hantan", 1); 

        setup();
}

void init()
{
        object me;
        int meqi, meneili, decqi, mq;
        me = this_player();

	if (! userp(me)) return;
        add_action("do_move", "enter");
        add_action("do_xun", "xun");

       if( query("id", me) == "qing long"
           || present("diyin xuemai", me))
        {
                tell_object(me, RED "你懷中的地陰血脈發出一陣陣熱"
                                "量，護住了周身的經脈！\n" NOR);
                return 0;
        }
        tell_object(me, HIW "你身陷碧水寒潭，潭中寒冰削肉刮骨，你"
                                "只覺渾身血液都被凍住一般！\n" NOR);
        set_temp("die_reason", "在碧水寒潭給活活凍死了", me);
        me->die();
        return 0;
}

int do_xun(string arg)
{
        object me = this_player();
        object ob;
        object ob1;

        if (objectp(present("qing long", environment(me))))
                return notify_fail("青龍已經現身了，還尋什麼呀，趕快戰鬥吧！\n");

        if (query("qinglong") < 1)
                return notify_fail("青龍已經被宰了，你再怎麼尋也是尋不到的！\n");

        if (me->is_busy())
                return notify_fail("你現在正忙着呢。\n");
       
        if( query("jing", me)<100 )
                return notify_fail("你太累了，稍微休息一下吧。\n");

        if( query("qi", me)<100 )
                return notify_fail("你太累了，稍微休息一下吧。\n");

        message_vision(HIC "\n$N" HIC "在洞內四處遊走，不放過半點蛛"
                       "絲馬跡，仔細的搜尋着洞穴內的一切。\n" NOR, me); 
        remove_call_out("xun"); 
        call_out("xun", 5, me);
        me->start_busy(5);
        return 1;
}
 
int xun(object me)
{ 
        object ob;
        object ob1;
        if (random(10) < 6)
        {
                me->receive_damage("jing", 50 + random(50));
                me->receive_damage("qi", 50 + random(50));
                me->start_busy(5);
                message_vision(WHT "$N" WHT "尋覓了半天，還是沒發現青"
                               "龍出沒的跡象，一口氣再也憋不住，連忙"
                               "游到洞的上部換氣。\n" NOR, me);
                return 1;
        }

        if (random(10) < 5)
        {
                me->receive_damage("jing", 50 + random(50));
                me->receive_damage("qi", 50 + random(50));
                me->start_busy(5);
                message_vision(HIY "結果$N" HIY "一轉身，雙腳不小心被"
                              "巖壁上伸出的水藻纏住，費了好大勁才掙扎"
                              "開。\n" NOR, me);
                return 1;
        }

   else if (random(10) < 4) 
        {         
                me->receive_damage("jing", 300 + random(50));
                me->receive_damage("qi", 300 + random(50));
                me->receive_wound("jing", 200 + random(50));
                me->receive_wound("qi", 200 + random(50));
                me->start_busy(5);
                message_vision(HIR "結果$N" HIR "翻轉身體時，“砰”的一"
                               "聲，頭撞在了尖突的巖壁上，登時鮮血飛濺，"
                               "痛得$N" HIR "“嗷嗷”怪叫不止。\n"
                               NOR, me);
                return 1;
        }

   else { 
                ob = new("/d/death/npc/qinglong");
                ob->move("/d/death/qinglongtan");
                addn("qinglong", -1);
                message_vision(HIW "\n\n只聽洞穴深處傳來震天動地的一聲"
                                   "怒嚎，叫聲震得你兩耳轟鳴，鼓膜隱隱"
                                   "作\n痛。你周圍的碧潭寒水急速捲動，"
                                   "激起滔天波浪，眼前一花，一個龐然大"
                                   "物\n出現在你面前，四神獸之首的青龍"
                                   "終於現身了。\n\n" NOR, me); 
                return 1;
        }
       
}

int do_move(string arg)
{
        object ob, paper,
        me = this_player();

        if (! arg || arg == "")
                return 0;

        if (arg == "xuanwo")
        {
                if ( objectp(present("qing long", environment(me))))
                {
                        write(HIW "\n青龍一聲怒嚎，龍尾直掃而出，劈打在你"
                              "身旁的巖壁上，石屑飛綻，擋住了去路。\n" NOR);
                        return 1;
                }
                message_vision(HIW "\n$N" HIW "你一縱身，跳進了寒流旋渦……\n"
                               NOR, me);
                me->move("/d/death/qiao1");
                message_vision(HIW "\n只見$N" HIW "被奈河橋下的寒流旋渦拋到空"
                                   "中，然後重重的跌落在奈河橋上。\n" NOR, me);
                set("neili", 0, me);
                set("jingli", 0, me);
                set("qi", 10, me);
                set("eff_qi", 10, me);
                set("jing", 10, me);
                set("eff_jing", 10, me);
                tell_object(me, HIR "你被跌得頭暈目旋，兩耳轟鳴，“哇”的噴出"
                                "一大口鮮血。\n" NOR);
                if( objectp(ob = present("diyin xuemai", me)) )
                        destruct(ob);
                tell_object(me, HIC "\n你懷中的" NOR + RED "地陰血脈" NOR +
                                HIC "耗盡能源，化作了一屢氣體飄出。\n" NOR);
                return 1;
        }
        return 0;
}
