#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "棧道");
        set("long", @LONG
棧道是通連接四川和中原的唯一道路，為了在險峻的山脈中打開
這條道路，不知道花費了多少人力物力，也不知死了多少人。這條路
是沿江而修成的，用大木樁釘在懸崖上，上面舖以木板，僅能過一兩
個人。棧道因年久失修，走在上面搖搖晃晃的，好不危險。 
LONG );
        set("exits", ([
                "east" : "/d/jingzhou/shangang",
                  "west" : __DIR__"shudao6",
           ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");
        set("objects", ([
                "/d/beijing/npc/tiaofu" : 1,
        ]));
        set("coor/x", -15030);
	set("coor/y", -1830);
	set("coor/z", -60);
	setup();
        replace_program(ROOM);
}