// /d/shenlong/huofang 伙房
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "伙房");
        set("long", @LONG
這裡是神龍教的伙房，房子的一邊是個灶爐，旁邊有一個老頭在往
灶內添柴，鍋內不知煮著是什麼東西，不過香味已經讓你饞得按捺不住
了。
LONG
        );
        set("exits", ([
                "south" : __DIR__"shibanlu",
        ]));
        set("objects",([
                __DIR__"obj/hongcha" : 3,
                __DIR__"obj/shegeng" : 2,
                __DIR__"obj/mitao" : 2,
                __DIR__"obj/longxx" : 1,
                __DIR__"obj/jiudai" : 2,
        ]));
        setup();
        replace_program(ROOM);
}
