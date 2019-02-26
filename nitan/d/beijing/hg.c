#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "皇宮大殿");
        set("long", @LONG
這裏便是紫禁城的正門的大殿，尋常百姓是到不了這裏來的，如
果你以不正當的途徑到了這裏，還是趕快離開為好。
LONG );
        set("exits", ([
                "north" : "/d/beijing/hgmen_n",
                "south" : "/d/beijing/hgmen_s",
                "west" : "/d/beijing/hg_w",
        ]));
        set("objects", ([
                "/d/beijing/npc/yuqian1" : 2,
        ]));
        set("outdoors", "beijing");
        set("coor/x", -190);
        set("coor/y", 4100);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
