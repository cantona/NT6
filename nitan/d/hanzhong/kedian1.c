// Last Modified by winder on Feb. 28 2001
// kedian1.c

inherit ROOM;

void create()
{
        set("short", "客店");
        set("long", @LONG
這是一家價錢低廉的客棧，生意非常興隆。外地遊客多選擇這裡
落腳，你可以在這裡打聽到各地的風土人情。店小二裡裡外外忙得團
團轉，接待著南腔北調的客人。客店的主人從不露面，他究竟是誰，
有各種各樣的猜測。牆上掛著一個牌子(paizi)。
LONG
        );
        set("no_fight", 1);
        set("valid_startroom", 1);
        set("no_sleep_room",1);

        set("item_desc", ([
                "paizi" : "樓上雅房，每夜十兩白銀。\n",
        ]));

        set("objects", ([
                __DIR__"npc/xiaoer1" : 1,
        ]));

        set("exits", ([
                "south" : __DIR__"dongjie",
                "up" : __DIR__"kedian2",
                "east"  : __DIR__"majiu",
        ]));
        set("coor/x", -12240);
	set("coor/y", 820);
	set("coor/z", 0);
	setup();
        "/clone/board/kedian17_b"->foo();
}

int valid_leave(object me, string dir)
{

        if( !query_temp("rent_paid", me) && dir == "up" )
        return notify_fail("店小二一下擋在樓梯前，白眼一翻：怎麼著，想白住啊！\n");

        if( query_temp("rent_paid", me) && dir == "south" )
        return notify_fail("店小二跑到門邊攔住：客官已經付了銀子，怎麼不住店就走了呢！
這不是砸小店的招牌嗎？\n");

        return ::valid_leave(me, dir);
}