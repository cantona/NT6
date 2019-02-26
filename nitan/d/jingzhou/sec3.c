#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "墳墓內部");
        set("long", @LONG
這裏放着一具棺材，大概就是墓碑上所寫「凌霜華」的棺材了。
奇怪的是棺材已被打開，旁邊放着棺蓋(cover)。
LONG );

        set("exits", ([
                "north" : __DIR__"sec2",
        ]));
        set("item_desc", ([
                "cover" : WHT "\n你抹去上面的灰塵，只看見上面竟然刻着些奇奇怪怪的數\n"
                          "字「" NOR + HIR "三十三" NOR + WHT "、" NOR + HIR "五"
                          "十七" NOR + WHT "、" NOR + HIR "一十八" NOR + WHT "、"
                          NOR + HIR "二十六" NOR + WHT "、" NOR + HIR "四十八" NOR
                          + WHT "……」 \n" NOR,
        ]));

        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
