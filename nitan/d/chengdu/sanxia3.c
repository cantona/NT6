#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "瞿塘峽");
        set("long", @LONG
這裏是長江三峽中的瞿塘峽，河水由東流來，進入此峽谷，河道
變窄，水流變急，兩岸的高山中間夾着一條河流，就好像一條絲帶一
般，蜿蜒而行。
LONG );
        set("exits", ([
                "east" :  __DIR__"sanxia2",
                "west" : __DIR__"shudao11",
        ]));
        set("objects", ([
                "/d/beijing/npc/youke" : 1,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");

        set("coor/x", -15060);
	set("coor/y", -1830);
	set("coor/z", -40);
	setup();
        replace_program(ROOM);
}