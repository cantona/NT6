// kedian.c
// Java Sep. 21 1998

inherit ROOM;

void create()
{
        set("short", "客店");
        set("long", @LONG
這是一家當地居民開的雞毛小店，樓下賣些鹵菜和劣酒，樓上則是
客房。這是在進祁連山區前的唯一休息之處，販夫走卒，採藥客等皆在
此休憩，不時還可看見一兩個尋仙訪道之輩。牆上有一塊牌子(paizi)，
西面是一間馬廄。
LONG);
        set("no_fight", 1);
        set("valid_startroom", 1);
        set("no_sleep_room",1);
        set("item_desc", ([
                "paizi" : "樓上雅房，每夜五兩白銀。\n",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));
        set("exits", ([
                "west" : __DIR__"majiu",
                "east" : __DIR__"yongdeng",
                "up"   : __DIR__"kedian2",
        ]));
        set("coor/x", -16120);
	set("coor/y", 4200);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if( !query_temp("rent_paid", me) && dir == "up" )
     return notify_fail("店小二一下擋在樓梯前，白眼一翻：怎麼著，想白住啊！\n");

        if( query_temp("rent_paid", me) && dir == "west" )
        return notify_fail("店小二跑到門邊攔住：客官已經付了銀子，怎麼不住店就住
旁人還以為小店伺候不周呢！\n");

        return ::valid_leave(me, dir);
}