#include <ansi.h>
inherit ROOM;

void create()
{
        set("short","水蓮洞內");
        set("long", @LONG
走到這裡就沒有路了，四周都是突起的怪石(stone)，洞壁上滲出
的水順著突石流了下來，水滴濺在地上發出『啪嗒，啪嗒』的聲音，
順著水流向上望去發現水流源頭處隱約有一絲光亮。但是那裡離地面
很高，站在下面也看不清楚。你往周圍一看，已找不到來時的路了，
不禁心下駭然。
LONG );
        
        set("item_desc",([
              "stone" : HIG "\n只見突石怪異嶙峋，水流正好順其而下。"
                        "石頭上面卻已經長滿了青苔。\n\n" NOR,
        ]));
        
        setup();

}


void init()
{        
        add_action("do_climb",({"climb","pa"}));
        add_action("do_tiao",({"tiao","jump"}));
}

int do_tiao(string arg)
{
        object me = this_player();
        
        if (! arg || arg != "stone")
                return notify_fail("你要往哪兒跳？\n");

        message_vision(HIC "\n$N縱身往突石上一跳，不料上面卻長滿了青苔，"
                        "$N一個不留神摔了下來，頓時暈了過去。\n\n" NOR,me);
        
        me->unconcious();

        return 1;
}


int do_climb(string arg)
{
        object me = this_player();

        if(! arg || arg != "stone")
                return notify_fail("你要往哪兒爬？\n");

        write(HIC "\n你走到洞壁旁，手拉上面突石，腳踩下面突石，"
              "不一會而便到了高處。\n\n" NOR);

        me->move(__DIR__"outzigai1");

         return 1;
}