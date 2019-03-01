// Room: /d/nanyang/kedian.c
// Last Modified by winder on Nov. 20 2001

inherit ROOM;

void create()
{
        set("short", "悅來客棧");
        set("long", @LONG
這是一家遠近聞名的悅來客棧，生意非常興隆。外地遊客多選擇在
這裡落腳，你可以在這裡打聽到各地的風土人情。店小二裡裡外外忙得
團團轉，接待著南腔北調的客人。牆上掛著一個牌子(paizi)。
LONG );
        set("valid_startroom", 1);
        set("no_fight", 1);
        set("item_desc", ([
                "paizi" : "樓上雅房，每夜五兩白銀。\n",
        ]));
        set("objects", ([
                __DIR__"npc/xiao-er" : 1,
                CLASS_D("misc") + "/xuxiake" : 1,
        ]));
        set("exits", ([
                "west" : __DIR__"nanyang",
                "east" : __DIR__"majiu",
                "up" : __DIR__"kedian2",
        ]));
//        set("no_clean_up", 0);
	set("coor/x", -6930);
	set("coor/y", 770);
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