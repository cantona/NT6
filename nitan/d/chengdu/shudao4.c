#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "江邊小路");
        set("long", @LONG
你走在長江邊上的一條小路上，再往西走，就進入了綿綿的四川
山區了，東南方向有條小路，不知道通往哪裏。
LONG );
        set("exits", ([
                  "east" :  __DIR__"shudao3",
                  "west" : __DIR__"shudao5",
           ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");

        set("coor/x", -180);
        set("coor/y", -180);
        set("coor/z", -60);
        setup();
        replace_program(ROOM);
}
