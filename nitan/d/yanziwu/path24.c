// Room: /d/yanziwu/path24.c
// Date: Jan.28 2000 by Winder

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "青草路");
        set("long", @LONG
沿着青草路，慢慢爬上蔓陀山峯。漸行漸高，慢慢的，山脊落在了
下面，波濤瀲灩的太湖慢慢佔據了你的視野。青天白雲，遠山飛雁，好
象越來越近了。
LONG );
        set("outdoors", "mantuo");
        set("no_clean_up", 0);
        set("exits", ([
                "southdown" : __DIR__"path23",
                "northup"   : __DIR__"luanyun",
                "east"      : __DIR__"tianfeng",
        ]));
        set("coor/x", 1210);
        set("coor/y", -1250);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}