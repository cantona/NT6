// Room: /d/wuxi/kedian.c
// Winder 2000/02/22

inherit ROOM;

void create()
{
        set("short", "客店");
        set("long", @LONG
這是一家價錢低廉的客棧，生意非常興隆。初次來到無錫的遊客大
多選擇這裡落腳，你可以在這裡打聽到各地的風土人情。店小二裡裡外
外忙得團團轉，接待著南腔北調的客人。客店的主人從不露面，他究竟
是誰，有各種各樣的猜測。牆上掛著一個牌子(paizi)。
LONG );
        set("no_fight", 1);
        set("valid_startroom", 1);
        set("no_sleep_room",1);
        set("no_clean_up", 0);
        set("item_desc", ([
                "paizi" : "賓至如歸\n樓上雅房，每夜五十兩白銀。\n",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));
        set("exits", ([
                "north" : __DIR__"majiu",
                "south" : __DIR__"westroad2",
                "up"    : __DIR__"kedian2",
        ]));

        set("coor/x", 1020);
	set("coor/y", -720);
	set("coor/z", 0);
	setup();
        "/clone/board/kedian8_b"->foo();
}

int valid_leave(object me, string dir)
{

        if( !query_temp("rent_paid", me) && dir == "up" )
        return notify_fail("店小二一下擋在樓梯前，白眼一翻：怎麼著，想白住啊！\n");

        if( query_temp("rent_paid", me) && dir == "south" )
        return notify_fail("店小二跑到門邊攔住：客官已經付了銀子，怎麼不住店就走了呢！
旁人還以為小店伺候不周呢！\n");

        return ::valid_leave(me, dir);
}