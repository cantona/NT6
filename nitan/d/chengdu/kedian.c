#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "錦城驛");
        set("long", @LONG
錦城驛是全西南最大的客店，生意非常興隆。外地遊客多選擇這
裡落腳，你可以在這裡打聽到各地的風土人情。店小二裡裡外外忙得
團團轉，沉重的川味官話你是實在聽不順耳。這是成都督府官辦的客
棧，接待著各地入川的官差浪人。牆上掛著一個牌子(paizi)。
LONG );
        set("no_fight", 1);
        set("valid_startroom", 1);
        set("no_sleep_room",1);

        set("item_desc", ([
                "paizi" : WHT "\n\n        ※※※※※※※※※※※※※※※※※\n"
                              "        ※                              ※\n"
                              "        ※    " NOR + HIW "樓上雅房，每夜十兩白銀。" NOR + WHT "  ※\n"
                              "        ※                              ※\n"
                              "        ※※※※※※※※※※※※※※※※※\n\n\n" NOR,
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));
        set("exits", ([
                "northwest" : __DIR__"southroad1",
                "up"        : __DIR__"kedian2",
                "east"      : __DIR__"majiu",
        ]));
        set("coor/x", -15200);
	set("coor/y", -1860);
	set("coor/z", 0);
	setup();
        "/clone/board/kedian3_b"->foo();
}

int valid_leave(object me, string dir)
{

        if( !query_temp("rent_paid", me) && dir == "up" )
                return notify_fail(CYN "店小二一下擋在樓梯前，白眼一翻：怎麼著，想白住啊？\n" NOR);

        /*
        if( query_temp("rent_paid", me) && dir == "east" )
                return notify_fail(CYN "店小二跑到門邊攔住：客官已經付了銀子，怎麼不住店就走了呢！\n" NOR);
        */

        return ::valid_leave(me, dir);
}