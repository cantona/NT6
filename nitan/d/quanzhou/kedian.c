// Room: /d/quanzhou/hongfulou.c
// Last Modified by winder on May. 29 2001
#include <room.h> 

inherit CREATE_CHAT_ROOM; 

void create()
{
        set("short", "鴻福樓");
        set("long", @LONG
這是泉州城中字號最老的客棧蒹酒樓，生意非常興隆。許多江湖人
物在這裡高談闊論，所以這裡是個打聽到情報的好地方。牆上掛著一個
牌子(paizi)。北面是一間馬廄。
LONG );
        set("item_desc", ([
                "paizi" : "樓上雅房，每夜五十兩白銀。\n",
        ]));
        set("exits", ([
                "west"   : __DIR__"northroad1",
                "north"  : __DIR__"majiu",
                "up"     : __DIR__"kedian2",
        ]));
        set("no_fight", 1);
        set("valid_startroom", 1);
        set("no_sleep_room",1);
        set("objects", ([
                __DIR__"npc/xiaoer2" : 1,
        ]));
	set("coor/x", -890);
	set("coor/y", -7660);
	set("coor/z", 0);
	setup();
        "/clone/board/kedian16_b"->foo();
        //"/adm/npc/youxun"->come_here();
}

void init() 
{
        add_all_action(); 
}

int valid_leave(object me, string dir)
{
        if( !query_temp("rent_paid", me) && dir == "up" )
                return notify_fail("店小二一下擋在樓梯前，白眼一翻：怎麼著，想白住啊！\n");

        if( query_temp("rent_paid", me) && dir == "west" )
                return notify_fail("店小二跑到門邊攔住：客官已經付了銀子，怎麼不住店就走了呢！\n旁人還以為小店伺候不周呢！\n");

        return ::valid_leave(me, dir);
}