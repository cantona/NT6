// Room: /d/mingjiao/gudi5.c

inherit ROOM;
void create()
{
        set("short", "昆侖仙境");
        set("long", @LONG
向西走了二裡多，只見峭壁上有一道大瀑布沖擊而下，料想是雪
融而成，陽光照射下尤如一條大玉龍，極是壯麗。瀑布泄在一座清澈
碧綠的深潭(tan )之中，潭水卻也不見滿，當是另有泄水的去路。你
觀賞了半晌，一低頭，見手足上染滿了青苔污泥，另有無數給荊棘硬
草割破的血痕，於是走近潭邊，除下鞋襪，伸足到潭水中去洗滌(xid
i)。
LONG );
        set("outdoors", "mingjiao");
        set("exits", ([
                "east" : __DIR__"gudi3",
        ]));
        set("fish_count",2);
        set("item_desc", ([
                "tan" : "你附身潭邊，凝神瞧去，只見碧綠的水中十餘條大白魚來回遊動。\n",
        ]));
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
        {
                message_vision("$N洗了一會，突然潑喇一聲，潭中跳起一尾大白魚，足有一尺多
長，$N忙伸手去抓，雖然碰到了魚身，卻一滑滑脫了。\n", me);
                return 1;
        }
        else
        {
                message_vision("潭中跳起一尾大白魚，足有一尺多長，$N忙伸手去抓，一把把它
攥在手心。\n", me);
                addn("fish_count",-1);
        }
        fish = new(__DIR__"obj/fish");
        fish -> move(me);
        return 1;
}
int reset()
{
        if (query("fish_count") < 2)
                addn("fish_count",1);
        ::reset();
        return 1;
}