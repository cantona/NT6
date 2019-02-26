// Room: /d/shaolin/bagua.c
// Date: YZC 96/01/19
// Date: CLEANSWORD 96/05/19

inherit ROOM;

void create()
{
        set("short", "八卦陣陣心");
        set("long", @LONG
這裏就是洪荒古陣的中心。站在這裏，才能看清楚四周的情形，
只見周圍暮藹沉沉，雲氣瀰漫，不見邊際。一道道閃電如奔蛇般穿梭
其間，發出陣陣悶雷。間夾着幾聲慘厲的哭叫聲，與雷電着地的劈裂
聲混合在一起，整個場面説不出的詭異可懼。陣心正中處有一口深潭
(tan)，望之深不見底。
LONG );
        set("item_desc", ([
                "tan":  "深潭邊的巖石上刻着四個巨大的古篆：“萬古寒潭”，\n"
                        "再有五個小字：“蒼松子謹書”。 潭邊都是極硬的玄武巖，\n"
                        "潭水澄碧透明，魚蝦不生。水面隱隱泛着一股幽幽的深綠色，\n"
                        "走近便覺一股徹骨寒氣撲面而來。  粗看似乎只有幾十丈深，\n"
                        "仔細望下去卻是越看越深，直如無底深淵一般！\n",
        ]));
        set("exits", ([
                "up" : __DIR__"andao3",
        ]));
        set("no_clean_up", 0);
        setup();
}

void init()
{
        add_action("do_enter", "enter");
}

int do_enter(string arg)
{
        object me;
        me = this_player();

        if( !arg || arg=="" ) return 0;

        if( arg=="tan" ) 
        {
                if( present("pishui zhu", me) ) 
                {
                        message_vision("$N取出闢水靈珠，含在嘴裏，輕輕一縱，躍入寒潭之中。\n", me);
                        me->move("/d/shaolin/hantan1");
                        message("vision", "只聽水面嘩啦一聲響，似乎有人也潛下水來。\n",
                                environment(me), ({me}) );
                }
                else
                {
                        tell_object(me, "你一跳入水中，只覺蝕骨寒氣從全身無數個毛孔侵入，四肢幾乎完全麻木，\n"
                                        "你拚着丹田中殘餘的一股內力，攀住潭邊的巖石，急急忙忙地爬了出來！\n");
                        message("vision", me->name() + "下半身一浸入水中，立刻大叫一聲，落湯雞似地跳了出來！，\n",
                                environment(me), ({me}) );
                }

                return 1;
        }
}
