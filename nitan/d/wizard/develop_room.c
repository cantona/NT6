// /d/wizard/guest_room.c

#include <ansi.h>
#include <room.h>
inherit ROOM;

int is_chat_room() { return 1; }

void create()
{
        set("short", HIM "遊戲開發室" NOR);
        set("long", @LONG
這裡是巫師和玩家交流的地方，為便于巫師統一管理，這裡只能
發表(post)關于玩家對本遊戲的見解以及開發建議或者對遊戲中某些
問題的疑問，以供巫師參考。不能發表非該主題以外的閒雜話題，如
果發現經過多次提醒仍然繼續者，將一律刪除檔案。其他問題請到「
巫師會客室」發表，這樣便于巫師和玩家交流，也便于統一管理，提
高效率！玩家可以在此發表任何符合該主題的文章，巫師也將盡力回
復之，並定期公布開發進度和計劃以供玩家參考，歡迎提出意見！  
                                  ==泥潭Ⅱ全體巫師==
LONG );

        set("exits", ([
                "north": __DIR__"guest_room",               
        ]));

        set("no_fight", 1);

        set("coor/x", 10000);
        set("coor/y", 9990);
        set("coor/z", 9990);
        setup();
        "/clone/board/develop_b"->foo();
}