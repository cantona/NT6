// /d/quanzhen/shulin1.c 樹林
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "樹林");
        set("long", @LONG
這位於終南山間的一大片樹林，生得頗為茂密。走在其間，只聽
得腳下沙沙的落葉聲，四周昏昏暗暗的，不時幾道日光穿過濃密的枝
頭，投射而下。偶爾遠處幾聲獸吼聲，更添了一分神祕感。往北和往
南各有一條小徑。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "north"      : __DIR__"baoziyan",
                "southdown"  : __DIR__"shanlu9",
        ]));

        set("coor/x", -3150);
        set("coor/y", 50);
        set("coor/z", 90);
        setup();
}
#include "caiyao.h"
