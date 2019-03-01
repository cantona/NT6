// qingjing.c 清凈居
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "清凈居");
        set("long", @LONG
這裡是全真七子之末，也是唯一的女弟子孫不二的居室。這房間
窗明幾凈，和她幾位師兄的臥室大不相同。床上折疊著一件道袍，袍
上繡著一個骷髏頭。這骷髏頭可不是隨便繡來嚇人的，是當年王重陽
收孫不二為徒時，畫了一副骷髏圖案給她，意思是說人生苦短，得道
為安。孫不二感念師恩，就將這個骷髏圖案繡在自己的道袍上。
LONG
        );
        set("exits", ([
                "north" : __DIR__"nairongdian",
        ]));

        set("objects", ([
                CLASS_D("quanzhen")+"/sun" : 1,
        ]));

        set("coor/x", -2780);
        set("coor/y", 90);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}