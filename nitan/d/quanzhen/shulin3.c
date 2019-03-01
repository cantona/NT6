// /d/quanzhen/shulin3.c 樹林
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "樹林");
        set("long", @LONG
這位於終南山間的一大片樹林，生得頗為茂密。走在其間，只聽
得腳下沙沙的落葉聲，四周昏昏暗暗的，不時幾道日光穿過濃密的枝
頭，投射而下。偶爾遠處幾聲獸吼聲，更添了一分神祕感。往北、南、
和東各有一條小徑。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "south"    : __DIR__"shenheyuan",
                "northup"  : __DIR__"juyan",
                "eastdown" : __DIR__"heifengdong",
        ]));

        set("coor/x", -3170);
        set("coor/y", 80);
        set("coor/z", 90);
        setup();
}
#include "caiyao.h"
