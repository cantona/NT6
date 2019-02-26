inherit ROOM;

void create()
{
        set("short", "客店");
        set("long", @LONG
這是一家價錢低廉的客棧，生意非常興隆。外地遊客很多都選擇這裏落
腳，你可以在這裏打聽到各地的風土人情。店小二里裏外外忙得團團轉，接
待着南腔北調的客人。
LONG
    );
        set("valid_startroom", 1);
       set("no_sleep_room",1);

        set("item_desc", ([
                "paizi" : "樓上雅房，每夜五兩白銀。\n",
        ]));

        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));

        set("exits", ([
        "east" : __DIR__"lx",
                "up" : __DIR__"kedian2",
        ]));

        setup();
        "/clone/board/kedian_b"->foo();
}

int valid_leave(object me, string dir)
{

        if( !query_temp("rent_paid", me) && dir == "up" )
        return notify_fail("怎麼着，想白住啊！\n");

        if( query_temp("rent_paid", me) && dir == "west" )
        return notify_fail("客官已經付了銀子，怎麼不住店就走了呢！
旁人還以為小店伺候不周呢！\n");

        return ::valid_leave(me, dir);
}