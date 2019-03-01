// Room: /heizhao/shiliang3.c
// Date: Dec. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "石樑");
        set("long", @LONG
石樑凹凸不平，又加終年在雲霧之中，石上溜滑異常，走得越
慢，反是越易傾跌。石樑到這裡忽然中斷，約有七八尺長的一個缺
口，缺口彼端盤膝坐著一個書生，手中拿了一卷書，正自朗誦。那
書生身後又有一個短短的缺口。缺口那邊一片荷塘邊上婆娑搖曳著
一排棕櫚
LONG );
        set("outdoors", "taoyuan");
        set("no_fight", 1);
        set("objects", ([
                CLASS_D("dali")+"/yideng/du" : 1,
        ]));
        set("exits", ([
                "south"  : __DIR__"shiliang2",
                "north"  : __DIR__"hetang",
        ]));
        set("coor/x", -5020);
        set("coor/y", -1230);
        set("coor/z", 40);
        setup();
        replace_program(ROOM);
}