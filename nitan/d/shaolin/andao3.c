// Room: /d/shaolin/andao3.c
// Date: YZC 96/02/06

#include <login.h>
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "暗道");
        set("long", @LONG
這是一個陰暗潮濕的地道，四壁用粗糙的片巖壘垛而成，一顆顆
水珠沿著牆壁滾下來，濺在地上。也許是因為長時間無人通行的緣故，
整個地道彌漫著一股腐屍般的惡臭。
LONG );
        set("exits", ([
                "up" : __DIR__"zhonglou1",
                "enter" : __DIR__"bagua0",
        ]));
        set("no_clean_up", 0);
        setup();
}

int valid_leave(object me, string dir)
{

        if ( dir == "up" )
        {
                if ( me->query_skill("jiuyang-shengong", 1) < 80 )
                {
                        return notify_fail("你試著推了推頂上的磚蓋，觸手冰涼，紋絲不動。\n" 
                        + "看來已被鐵汁澆透，堅如鐵板一般。看來你只能另想辦法了。\n");
                }                

                message_vision( HIY
                "$N全身運足九陽真氣，拔身錯步，嘿地一聲，舉起雙掌向上猛擊。\n"
                "只見一股白氣自$N掌心而出，迅猛無比地擊中頂上的鐵鑄磚蓋。\n"
                "克剌剌一聲巨響，磚蓋被震成無數小碎片四散飄飛。露出一個向上的洞口。\n" NOR, me );

        }

        return ::valid_leave(me, dir);
}

//坎; 離; 震; 艮; 艮; 兌; 巽; 震; 乾; 震; 兌; 巽; 離; 坎; 兌; 艮; 兌; 坎

