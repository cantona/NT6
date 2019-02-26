// Room: /heizhao/houyuan.c
// Date: Dec. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "後院");
        set("long", @LONG
後院正中供奉着彌勒歡喜佛，佛像背面挺立着一個威猛的手持
長杵的護法韋陀。房內蒲團上居中坐着一個老僧，銀鬚垂胸，厚厚
的僧衣直裹到面頰，正自低眉入定。有幾名老和尚、小沙彌侍立兩
旁。
LONG );
        set("no_clean_up", 0);
        set("objects", ([
                __DIR__"npc/xiaoshami2" : 2,
                __DIR__"npc/laoheshang" : 1,
                CLASS_D("duan") + "/yideng" : 1,
                //CLASS_D("dali")+"/yideng/yideng" : 1,
        ]));
        set("exits", ([
                "south"  : __DIR__"zhulin1",
        ]));
        set("coor/x", -5020);
        set("coor/y", -1000);
        set("coor/z", 50);
        setup();
        replace_program(ROOM);
}