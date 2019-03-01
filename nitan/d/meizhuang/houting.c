#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "後廳");
        set("long", @LONG
這裡是孤山梅莊的後廳，後廳內相當的寬敞明亮，四周的牆上懸
掛滿了各朝名人的真跡，正堂坐著一個極高極瘦的黑衣老者，那老者
眉清目秀，只是臉色泛白，似乎是一具僵屍模樣，令人一見之下，心
中便感到一陣涼意。大廳往南是一條走廊。
LONG );
        set("exits", ([
            "south" : __DIR__"zoulang3",
        ]));

        set("objects", ([
                CLASS_D("meizhuang") + "/heibai" : 1,
        ]));

        set("no_clean_up", 0);
        set("valid_startroom", 1);
        setup();
        "/clone/board/meizhuang_b"->foo();
        replace_program(ROOM);
}