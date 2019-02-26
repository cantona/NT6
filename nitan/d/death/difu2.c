// difu2.c

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIW "酆都地府" NOR);
        set("long",BLU @LONG
這裏就是陰間鬼魂都必須通過的酆都城，是冥府的中心。往南不遠
處就是著名的鬼門關，鬼魂進了鬼門關，就再也不能回頭了。四下裏影
影幢幢，但是卻聽不到半點聲音，不時有鬼魂從你身邊而過，你卻摸它
不到，一切都想在夢裏一樣。東邊是一個小店，店門沒有關，卻無風自
晃，「岡當岡當」地響着。北面有一個大殿，黑漆漆的。
LONG NOR );
        set("no_fight", 1);
        set("exits", ([
                "north" : __DIR__"dadian",
                "south" : __DIR__"difu1",
                "west"  : __DIR__"inn1",
                "east"  : __DIR__"inn2",
        ]));
        set("objects", ([
                __DIR__"npc/yeyou": 1,
                __DIR__"npc/riyou": 1,
        ]) );

        setup();
        replace_program( ROOM );
}
