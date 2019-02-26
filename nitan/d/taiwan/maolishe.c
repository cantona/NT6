// Room: /d/taiwan/maolishe.c
// Last Modifyed by Ahda on Jan. 4 2002

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "貓里社");
        set("long", @LONG
貓里社位於竹塹西南。清朝初年，此地的漢人還很少，居住在這裏
的主要是泰雅族人，他們以漁獵為生。
LONG );
        set("exits", ([
                "eastup"    : __DIR__"dabajianshan",
                "northeast" : __DIR__"zhuqian",
                "southwest" : __DIR__"banxianshe",
        ]));
        set("objects", ([
                __DIR__"npc/taiyaren": 1,
        ]));

        set("outdoors", "taiwan");
        set("coor/x", 2520);
        set("coor/y", -6990);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
