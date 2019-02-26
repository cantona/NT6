// Room: /lingzhou/chema.c
// Java Sep. 23 1998

inherit ROOM;

void create()
{
        set("short", "車馬店");
        set("long", @LONG
一家低檔的車馬客棧，建築相當陳舊，很不起眼，不過由於價錢低
廉，又是在北門的交通要道上，三教九流多選擇這裏落腳，生意也相當
不錯，你也可以在這裏打聽到當地的風土人情。
    牆上掛着一個牌子(paizi)。
LONG );
        set("no_fight", 1);
        set("no_sleep_room",1);
        set("item_desc", ([
                "paizi" : "樓上雅房，每夜十兩白銀。\n",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));
        set("exits", ([
                "east" : __DIR__"majiu",
                "west" : __DIR__"nandajie",
                "up"   : __DIR__"chema2",
        ]));
        set("coor/x", -6275);
        set("coor/y", 2915);
        set("coor/z", 0);
        setup();
        "/clone/board/kedian12_b"->foo();
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