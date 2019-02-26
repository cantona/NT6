//Edited by fandog, 02/15/2000
inherit ROOM;

void create()
{
        set("short", "晴川客棧");
        set("long", @LONG
這是一家價錢低廉的客棧，生意非常興隆。外地遊客多選擇這裏落
腳，你可以在這裏打聽到各地的風土人情。店小二里裏外外忙得團團轉，
接待着南腔北調的客人。牆上掛着一個牌子(paizi)。
LONG );
        set("no_fight", 1);
        set("valid_startroom", 1);
        set("no_sleep_room",1);
//        set("no_clean_up", 0);
        set("item_desc", ([
                "paizi" : "樓上雅房，每夜五十兩白銀。\n",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));
        set("exits", ([
                "south" : __DIR__"majiu",
                "north" : __DIR__"hzjie4",
                "up"   : __DIR__"kedian2",
        ]));

	set("coor/x", -5100);
	set("coor/y", -1890);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{

        if( !query_temp("rent_paid", me) && dir == "up" )
        return notify_fail("店小二一下擋在樓梯前，白眼一翻：怎麼着，想白住啊！\n");

        if( query_temp("rent_paid", me) && dir == "north" )
        return notify_fail("店小二跑到門邊攔住：客官已經付了銀子，怎麼不住店就走了呢！
旁人還以為小店伺候不周呢！\n");

        return ::valid_leave(me, dir);
}