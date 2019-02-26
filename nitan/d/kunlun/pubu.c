// Room: /d/kunlun/pubu.c
// Last Modified by winder on Jun. 29 2001

inherit ROOM;
void create()
{
        set("short", "瀑布");
        set("long", @LONG
向西走了二里多，只見峭壁上有一道大瀑布衝擊而下，料想是雪融
而成，陽光照射下尤如一條大玉龍，極是壯麗。瀑布泄在一座清澈碧綠
的深潭(tan )之中，潭水卻也不見滿，當是另有泄水的去路。你觀賞了
半晌，一低頭，見手足上染滿了清苔污泥，另有無數給荊棘硬草割破的
血痕，於是走近潭邊，除下鞋襪，伸足到潭水中去洗滌(xidi)。
LONG );
        set("outdoors", "hongmei");
        set("exits", ([
                "east" : __DIR__"cuigu",
        ]));
        set("no_clean_up", 0);
        set("fish_count",2);
        set("item_desc", ([
                "tan": "你附身潭邊，凝神瞧去，只見碧綠的水中十餘條大白魚來回遊動。\n",
        ]));
        set("coor/x", -100020);
        set("coor/y", 20050);
        set("coor/z", 40);
        setup();
}
void init()
{
        add_action("do_xidi", "xidi");
}
int do_xidi()
{
        object fish, me = this_player();
        if ((this_player()->query_dex()<25) || query("fish_count")<=0)
                message_vision("$N洗了一會，突然潑喇一聲，潭中跳起一尾大白魚，足有一尺多\n長，$N忙伸手去抓，雖然碰到了魚身，卻一滑滑脱了。\n", me);
        else
        {
                message_vision("$N洗了一會，突然潑喇一聲，潭中跳起一尾大白魚，足有一尺多\n長，$N忙伸手去抓，一把把它攥在手心。\n", me);
                addn("fish_count",-1);
        }
        fish = new(__DIR__"obj/fish");
        fish -> move(me);
        return 1;
}
