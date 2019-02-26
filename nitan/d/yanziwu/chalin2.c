// Room: /d/yanziwu/chalin2.c
// Date: Jan.28 2000 by Winder

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
                "west"  : __DIR__"chalin4",
                "east"  : __DIR__"chalin2",
                "south" : __DIR__"chalin2",
                "north" : __DIR__"chalin3",
        ]));
        set("coor/x", 1200);
        set("coor/y", -1280);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}