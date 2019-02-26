// This program is a part of NT MudLIB

inherit ROOM;

void create()
{
        set("short", "花園");
        set("long", @LONG
這裏是翰林府的花園。院子裏種了各色名貴的菊花。黃菊有都勝、
金芍藥、報君知。白菊有月下白、一團雪、貂蟬拜月。紫菊有雙飛燕、
紫玉蓮、瑪瑙盤。紅菊有美人紅、醉貴妃、繡芙蓉。。。院中有幾盆
顏色特別嬌豔的黃花，花瓣黃得像金子一樣，花朵的樣子很像荷花。
那就是從天竺傳來的金波旬花。
LONG );
        set("outdoors", "jingzhou");
        set("region", "jingzhou");

        set("exits", ([
                "north" : __DIR__"houyuan",
                "west" : __DIR__"loudi",
                "east" : __DIR__"shufang",
        ]));
        set("objects", ([
                //__DIR__"npc/obj/juhua1" : 1,
                __DIR__"obj/jinboxunhua" : 2,
        ]));

        set("coor/x", -7110);
	set("coor/y", -2090);
	set("coor/z", 0);
	setup();
}

void init()
{
        object me = this_player();

        if( !query_temp("jinboxunhua", me) && !wizardp(me) && playerp(me)){
                me->receive_damage("qi", 1000);
                me->receive_damage("jing", 800);
                set_temp("die_reason", "中了金波旬花毒而死", me);
                tell_object(me, "你突然頭暈目旋。\n");
                return;
        }
}