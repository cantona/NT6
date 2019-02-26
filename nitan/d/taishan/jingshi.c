// Room: /d/taishan/jingshi.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;
int do_study(string arg);

void create()
{
        set("short", "經石峪");
        set("long", @LONG
這裏是一塊大石坪，石面刻有篆文「金剛經」，字體其大如鬥，但
卻沒有記載刻石者的名字和刻石的年代。經石峪四面環山，深谷幽奧。
龍泉峯聳峙於東，鋭若茁筍；炮高嶺橫亙於西；澗水自東北三叉溝亂石
中泠泠而出，繞龍泉峯流入中溪。
LONG );
        set("exits", ([
                "westdown"  : __DIR__"doumo",
                "northwest" : __DIR__"shijian",
        ]));
        set("objects",([
                __DIR__"npc/seng-ren" : 1,
        ]));
        set("outdoors", "taishan");
        set("coor/x", 80);
	set("coor/y", 130);
	set("coor/z", 60);
	setup();
}

void init()
{
        add_action("do_study", "study");
        add_action("do_study", "du");
}


int do_study(string arg)
{
        object me;

        me = this_player();

        if ( !arg || ( arg != "stone" ) )
                return notify_fail("什麼？\n");

        if ( (int)me->query_skill("literate", 1) < 1)
                return notify_fail("你是個文盲，先學點文化(literate)吧。\n");

        if( query("jing", me)<40 )
                return notify_fail("你現在太累了，什麼也沒學進去。\n");

        me->receive_damage("jing", 30);

        message_vision("$N正專心研讀石坪上的「金剛經」。\n", me);

        if ( (int)me->query_skill("buddhism", 1) < 100)
        {
                me->improve_skill("buddhism",query("int", me));
                write("你對着石坪上的「金剛經」琢磨了一回兒，似乎對禪宗心法略有心得。\n");
                return 1;
        }

        write("你對着石坪瞧了一回兒，發現上面所説的佛理太過淺顯，對你來説已毫無意義了。\n");

        return 1;
}