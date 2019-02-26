inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "玄冥谷");
        set("long", @LONG
這是玄冥谷了，但見四周羣峯圍繞，山石掩映，前方不遠
處有幾間小屋(room)，偶有山鹿追逐嬉戲，飛鳥齊鳴，猶如置
身於世外桃源一般。遠遠望見玄冥峯上白雪一片，雲霧繚繞於
四周，令人心曠神怡。
LONG );
        set("exits", ([
                "southup"    : __DIR__"shanlu3",
                "northwest"  : __DIR__"shanlu4",
                "enter"      : __DIR__"xiaowu",
        ]));

        set("objects", ([
                "/kungfu/class/xuanming/lu" : 1,
        ]));

        set("item_desc", ([
                "room"  : NOR + YEL "一間簡陋的茅草屋，可以在裏面休息練功。\n" NOR,
        ]));

        set("outdoors", "xuanming");
        setup();
        replace_program(ROOM);
}