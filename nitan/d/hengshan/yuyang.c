// Room: /d/hengshan/yuyang.c
// Date: Oct. 2 1997 by That

#include <room.h>
inherit ROOM;
void create()
{
        set("short", "玉羊遊雲");
        set("long", @LONG
在東峰峭壁崖頂上，白石累累，散布有致，在雲霧拂動下，似有動
感，象正在吃草的羊只。這就是和“金雞報曉”齊名的恆山勝景“玉羊
遊雲”。
LONG);
        set("exits", ([ /* sizeof() == 4 */
                "westdown"    : __DIR__"beiyuedian",
        ]));
        set("outdoors","hengshan");
        set("no_clean_up", 0);
        set("coor/x", 40);
        set("coor/y", 3180);
        set("coor/z", 80);
        setup();
        replace_program(ROOM);
}
