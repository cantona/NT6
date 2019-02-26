// Room: /d/yanziwu/chalin6.c
// Date: Jan.28 2000 by Winder
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "茶花林");
        set("long", @LONG
你在花林中跌跌撞撞地蹣跚而行，不知道那裏是出口，來時所留神
的只是茶花，忘了記憶路徑，眼見小路東一條、西一條，也不知那一條
才是來路，要回到小船停泊處卻有點兒難了，於是你心想：“先走到水
邊再説。”
LONG );
        set("outdoors", "mantuo");
        set("no_clean_up", 0);
        set("exits", ([
                "west"  : __DIR__"chalin3",
                "east"  : __DIR__"chalin1",
                "south" : __DIR__"dukou",
                "north" : __DIR__"chalin5",
        ]));
        set("coor/x", 1200);
        set("coor/y", -1290);
        set("coor/z", 0);
        setup();
}
int valid_leave(object me, string dir)
{
        if (dir == "south")
                tell_object(me,HIY"你總算出了茶花林。\n"NOR);
        return ::valid_leave(me, dir);
}