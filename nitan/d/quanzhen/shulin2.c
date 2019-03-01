// /d/quanzhen/shulin2.c 樹林
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "樹林");
        set("long", @LONG
這位於終南山間的一大片樹林，生得頗為茂密。走在其間，只聽
得腳下沙沙的落葉聲，四周昏昏暗暗的，不時幾道日光穿過濃密的枝
頭，投射而下。偶爾遠處幾聲獸吼聲，更添了一分神祕感。往西北和
往東各有一條小徑。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "northwest"  : __DIR__"shenheyuan",
                "east"       : __DIR__"baoziyan",
        ]));
        set("objects", ([
                "/d/quanzhen/npc/deer": 1,
        ]));
        set("coor/x", -3160);
        set("coor/y", 60);
        set("coor/z", 90);
        setup();
}

#include "caiyao.h"
