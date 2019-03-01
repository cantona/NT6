#include <room.h>
#include <ansi.h>

inherit CREATE_CHAT_ROOM;

void create()
{
	set("short", "客店");
        set("long", @LONG
這是一家價錢低廉的客棧，生意卻是非常興隆。外地遊客多選擇
在這裡落腳，你可以在這裡打聽到各地的風土人情。店小二裡裡外外
忙得團團轉，接待著南腔北調的客人。客店的主人從不露面，他究竟
是誰，有各種各樣的猜測。客店的西牆上掛著一個牌子(paizi)。
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
                __DIR__"npc/fuxinglaoren" : 1,
                __DIR__"npc/xiaoer" : 1,
                __DIR__"npc/qi"     : 1,
                "/u/shulele/shashou/npc/yangxu-yan.c" : 1,
	]));
	set("exits", ([
                "east" : __DIR__"majiu",
          "service":"/d/city/advice/advice",
		"west" : __DIR__"beidajie1",
		"up"   : __DIR__"kedian2",
		"south": __DIR__"kedian4",
                "north": __DIR__"stock",
	]));


	set("coor/x", 10);
	set("coor/y", 10);
	set("coor/z", 0);
	setup();
	"/clone/board/kedian_b"->foo();
        "/adm/npc/youxun"->come_here();
}

void init()
{
        add_all_action();
}

int valid_leave(object me, string dir)
{

	if( !query_temp("rent_paid", me) && dir == "up" )
	        return notify_fail(CYN "店小二一下擋在樓梯前，白眼一翻：怎麼著，想白住啊？\n" NOR);

	if( query_temp("rent_paid", me) && dir == "west" )
	        return notify_fail(CYN "店小二跑到門邊攔住：客官已經付了銀子，怎麼不住店就走了呢！\n" NOR);

	return ::valid_leave(me, dir);
}
