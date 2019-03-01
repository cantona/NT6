// /d/taishan/kedian.c

inherit ROOM;

void create()
{
        set("short", "客棧");
        set("long", @LONG
這是一家在泰山山腳一的一個小客棧，由于泰山遊人如織，因此這
裡生意非常興隆。外地遊客多選擇在這裡落腳，你可以在這裡打聽到各
地的風土人情。店小二裡裡外外忙得團團轉，接待著南腔北調的客人。
牆上掛著一個牌子(paizi)。
LONG );
        set("valid_startroom", 1);
        set("no_fight", 1);
        set("item_desc", ([
                "paizi" : "樓上雅房，每夜五兩白銀。\n",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));
        set("exits", ([
                "west" : __DIR__"taishanjiao",
                "up"   : __DIR__"kedian2",
        ]));
        set("coor/x", 80);
	set("coor/y", 30);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if( !query_temp("rent_paid", me) && dir == "up" )
        return notify_fail("店小二一下擋在樓梯前，白眼一翻：怎麼著，想白住啊！\n");

        if( query_temp("rent_paid", me) && dir == "west" )
        return notify_fail("店小二跑到門邊攔住：客官已經付了銀子，怎麼不住店就走了呢！
旁人還以為小店伺候不周呢！\n");

        return ::valid_leave(me, dir);
}