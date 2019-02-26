// Room: /d/huashan/lianhua.c

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "蓮花峯");
        set("long", @LONG
太華西峯－又名蓮花峯，也叫芙蓉峯，峯頂有一塊巨石，狀如蓮
花，覆蓋崖巔。該處由此得名。這裏懸崖陡峭，壁立千仞，登臨遠眺
（tiao），秦川莽莽，渭、洛二水盤屈如帶。峯頂有石名『摘星石』，
取『手可摘星辰』之意，以狀西峯之高。
LONG );
        set("exits", ([ /* sizeof() == 4 */
             "eastdown" : __DIR__"chengxiang",
        ]));

        set("item_desc", ([
               "jianzhong" : "太遠了瞧不清楚。\n",
        ]));

        set("outdoors", "huashan");

        setup();
}
 
void init()
{
        object me = this_player();
        if( query_temp("xunshan", me))set_temp("xunshan/lianhua", 1, me);

        add_action("do_tiao", "tiao");
        add_action("do_jump", "jump");

        return;
}

int do_tiao()
{
        object me = this_player();

        write(@LONG
但見遠處峭壁如一座極大的屏風，沖天而起，峭壁中部離地約二十餘丈處，生
著一塊三四丈見方的大石，便似一個平台，石上隱隱刻得有字。極目上望，瞧
清楚乃是「劍冢」（jianzhong）兩個大字。
LONG);

        return 1;
}

int do_jump(string arg)
{
        object me = this_player();

        if (! arg || arg != "jianzhong")
             return notify_fail("你要往哪兒跳？\n");

        if( query("qi", me)<300 )
             return notify_fail("你力氣不加。\n");

        if (me->is_busy() || me->is_fighting())
             return notify_fail("等你忙完了再説。\n");

        me->start_busy(1 + random(3));

        if (me->query_skill("dodge", 1) < 200 || me->query_str() < 30)
        {
             message_vision(HIG "$N" HIG "提一口氣，竄高數尺，往蓮花峯上峭壁跳去 ……\n"
                            HIR "$N" HIR "爬了十來丈，已然力氣不加，當即摔了下來，渾身鮮血直流。\n" NOR, me);
   
             me->receive_wound("qi",query("qi", me)/2,me);
            
             return 1;
        }

        message_sort(HIG "\n$N" HIG "縱身躍起，竄高數尺，左足踏在峭壁上的小洞之中，跟"
                     "着竄起，右足對準一叢青苔踢了進去，軟泥迸出，石壁上竟然又有一個"
                     "小穴可以容足，$N" HIG "深吸一口氣，雙臂抓住石壁上突出的石塊，猛地"
                     "用力一躍，跳上了峭壁。\n" NOR, me);

       me->move(__DIR__"jianzhong");
      
       return 1;
}
