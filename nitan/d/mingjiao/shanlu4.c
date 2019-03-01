#include <room.h>

inherit ROOM;

void create()
{
        set("short", "青石階");
        set("long", @LONG
這裡山路漸寬，青石舖路，苔痕淡青，路左青鬆巍巍，路右籐蘿
繞樹，遠遠的，只見前方房宇依稀，赤紅色旗幟招展，聽說明教烈火
旗在此據守，數百年來固如磐石。
LONG );
        set("exits", ([
                "southdown" : __DIR__"shanlu3",
                "northup"   : __DIR__"lhqpaifang",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "mingjiao");
        setup();
        replace_program(ROOM);
}