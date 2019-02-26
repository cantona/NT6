#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "古樹頂");
        set("long", @LONG
你極目遠眺，四周盡是懸崖峭壁。一條樹藤(teng)從你面前垂下。
忽然間你看見前面峭壁上似乎有一個山洞(hole)，但是距離甚遠卻是
怎麼也過不去。
LONG );
        set("exits", ([ 
               "down" : __DIR__"ontree",
           ]));

        set("item_desc", ([
               "hole"    : HIC "\n太遠了，看得不太清楚，看來得想個辦法過去。\n"        NOR,
           
               "teng"    : YEL"\n這些樹藤看起來很結實，看來可以拉着根樹藤跳過去。\n" NOR,
        ]));


        setup();
}

void init()
{
       add_action("do_la", "la");
       add_action("do_tiao", "tiao");
      
}

int do_la(string arg)
{
        object me;

        me = this_player();
        
        if (! arg || arg != "teng")
                return notify_fail("你想幹什麼？\n");

        if (me->is_busy() || me->is_fighting())
                return notify_fail("等你忙完了再説。\n");

        if( query_temp("la_teng", me) )
                return notify_fail("你已經拉着了啊？\n");

        message_vision(NOR + YEL "$N" NOR + YEL "雙手緊緊拉住樹藤，看起來很"
                       "結實。\n" NOR, me);

        set_temp("la_teng", 1, me);
                  
        return 1; 
        
}

int do_tiao(string arg)
{
        object me;

        me = this_player();
        
        if (! arg || arg != "hole")
                return notify_fail("你想幹什麼？\n");

        if (me->is_busy() || me->is_fighting())
                return notify_fail("等你忙完了再説。\n");

        if( !query_temp("la_teng", me) )
                return notify_fail("太遠了，這樣恐怕跳不過去！\n");

        if (random(6) != 1)
        { 
              message_sort(HIC "\n$N" HIC "雙手緊緊拉住樹藤，騰空而起，向山洞跳去。但是樹藤“啪~”的一聲"
                           "在半空斷掉，$N " HIC "重重地摔了下去……\n\n" NOR, me);
              me->move(__DIR__"xuanyadi");
              delete_temp("la_teng", me);
              me->unconcious();
              return 1;
       }

       message_sort(HIC "\n$N" HIC "雙手緊緊拉住樹藤，騰空而起，向山洞跳去，樹藤在空中劃出一道美妙的弧線。"
                    "$N" HIC "只覺耳邊風聲呼呼……很快$N" HIC "輕輕地落在了洞口，回頭望見樹藤在空中搖擺"
                    "着！\n\n" NOR, me);

      delete_temp("la_teng", me);
      me->move(__DIR__"outzhushendong");     
          
      return 1; 
        
}