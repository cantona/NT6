#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW "白帝城" NOR );
        set("long", @LONG
朝辭白帝彩雲間，千裡江陵一日還。兩岸猿聲啼不住，千舟以過
萬重山。這裡就是有名的白帝城了，遙看四周，只見青山綠水，一片
大好風景。廟內塑有劉備及孔明等一幹名士的雕像，憑欄懷古，心潮
洶湧，令人神怡。
LONG );
        set("exits", ([
                  "west" : __DIR__"shudao10",
                "east" : __DIR__"sanxia3",
                "north": __DIR__"shandao",
  
        ]));
        set("objects", ([
                "/d/beijing/npc/shiren" : 1,
                "/d/beijing/npc/shusheng1" : 2,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");
        set("coor/x", -15070);
	set("coor/y", -1830);
	set("coor/z", -40);
	setup();
        replace_program(ROOM);
}