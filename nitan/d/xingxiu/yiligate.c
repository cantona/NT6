// Room: /d/xingxiu/yili1.c
// Last Modified by winder on Apr. 25 2001
#include <ansi.h>
inherit ROOM;
void quarter_pass();

void create()
{
        set("short", "伊犁城南門");
        set("long", @LONG
伊犁，又名惠遠，西通波斯，南到天竺，東與陽關、玉門相連，扼
中西交通的要衝，是絲綢之路上重要的旅站之一。伊犁城牆在伊犁河北
岸度地而築，城高一丈四，地勢險要。城牆上滿布着炮台、槍眼，戒備
森嚴。
LONG
        );
        set("outdoors", "xiyu");
        set("exits", ([
                "south" : __DIR__"yilihe",
                "north" : __DIR__"yili",
        ]));

        set("objects", ([
                __DIR__"npc/bing" : 2,
                __DIR__"npc/wujiang" : 2,
                __DIR__"npc/trader" : 1,
        ]));
        set("coor/x", -39000);
        set("coor/y", 12000);
        set("coor/z", 0);
        setup();
//        quarter_pass();
}
/*
void quarter_pass()
{
        mixed *local;

        local = localtime(time() * 60);
        if (local[2] < 6 || local[2] >= 21)
        {
                set("long", @LONG
伊犁，又名惠遠，西通波斯，南到天竺，東與陽關、玉門相連，扼
中西交通的要衝，是絲綢之路上重要的旅站之一。伊犁城牆在伊犁河北
岸度地而築，城高一丈四，地勢險要。城牆上滿布着炮台、槍眼，戒備
森嚴。現在是夜間，城門已關，只有幾個回族士兵在城門口守夜。
LONG);
                delete("exits/north");
        }
        else {
                set("long", @LONG
伊犁，又名惠遠，西通波斯，南到天竺，東與陽關、玉門相連，扼
中西交通的要衝，是絲綢之路上重要的旅站之一。伊犁城牆在伊犁河北
岸度地而築，城高一丈四，地勢險要。城牆上滿布着炮台、槍眼，戒備
森嚴。
LONG);
                set("exits/north", __DIR__"yili2");
        }
        call_out("quarter_pass", 30);
}
*/