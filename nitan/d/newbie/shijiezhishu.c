#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIG "世界之樹" NOR);
        set("long", @LONG
這裏是古村的正中心，一個很寬闊的廣場，上面鋪着青石地面。中
央一棵大樹(tree)盤根錯節，已經看不出它究竟有着多大的樹齡了，它
就是傳説中的世界之樹——傳説就是它帶來了整個世界的綠色，是自然
之祖。樹下站着一個老者，正耐心地輔導着新手。

==== 如果你需要幫助請輸入指令 ask lao about here ====

LONG);
        set("item_desc", ([
                 "tree" : GRN "\n這是一棵巨大古老的大樹，枝葉非常"
                         "的茂密。\n" NOR,
        ]));

        set("objects", ([
                __DIR__"npc/laocunzhang" : 1,
        ]));

        set("valid_startroom", 1);
        set("exits", ([
                "east"  :  __DIR__"road2",
                "west"  :  __DIR__"road",
        ]));

        set("xinshoucun", 1);
        set("outdoors", "newbie");
        
        set("no_fight", 1);
        setup();

        "/clone/board/newbie_b"->foo();
        replace_program(ROOM); 
}
