// Room: /d/fuzhou/rongcheng.c
// Date: May 12.1998 by Java
inherit ROOM;

void create()
{
        set("short", "榕城驛");
        set("long", @LONG
榕城驛是全省最大的客店，生意非常興隆。外地遊客多選擇這裏落
腳，你可以在這裏打聽到本省的風土人情。店小二里裏外外是忙得團團
亂轉，福州的方言你是實在聽不順耳。還是上樓睡覺去。
    牆上掛着一個牌子(paizi)。
LONG );
        set("no_fight", 1);
        set("valid_startroom", 1);
        set("no_sleep_room",1);

        set("item_desc", ([
                "paizi" : "樓上雅房，每夜五十兩白銀。\n",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));
        set("exits", ([
            "south" : __DIR__"dongdajie",
            "north" : __DIR__"majiu",
            "up"    : __DIR__"rongcheng2",
        ]));
	set("coor/x", -70);
	set("coor/y", -6170);
	set("coor/z", 0);
	setup();
        "/clone/board/kedian5_b"->foo();
}

int valid_leave(object me, string dir)
{
        if( !query_temp("rent_paid", me) && dir == "up" )
        return notify_fail("店小二一下擋在樓梯前，白眼一翻：怎麼着，想白住啊！\n");

        if( query_temp("rent_paid", me) && dir == "west" )
        return notify_fail("店小二跑到門邊攔住：客官已經付了銀子，怎麼不住店就走了呢！
旁人還以為小店伺候不周呢！\n");

        return ::valid_leave(me, dir);
}