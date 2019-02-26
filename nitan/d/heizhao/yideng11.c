//Cracked by Kafei
// yideng quest room 11

#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "廟內廂房");
        set("long", @LONG
這裏是廟的東廂房，有小沙彌奉上香茶待客。廟宇看來雖小，裏
邊卻甚進深，一條青石鋪的小徑穿進後面的一座竹林，竹林綠蔭森森，
幽靜無比，令人煩俗盡消。竹林中隱着三間石屋。
LONG );

        set("exits", ([
                "out" : __DIR__"yideng9",
                "north" : __DIR__"yideng12",
        ]));

        set("invalid_startroom", 1);
        set("coor/x", -38000);
        set("coor/y", -80000);
        set("coor/z", 500);
        setup();
}