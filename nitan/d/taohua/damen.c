#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "桃花山莊正門");
        set("long",@LONG
這裏是桃花島的正門。門前疏落地種了幾株桃花樹，更顯
得此地主人對桃花的偏愛。門口站着兩個小童看守大門。看來
由於地處邊遠人煙罕至，人們對山莊的防衞不是特別謹慎。門
前有一對白雕(diao)，毛羽如雪，甚為可愛。
LONG);
        set("outdoors", "taohua");
        set("exits", ([
                "south" : __DIR__"qianyuan",
                "north" : __DIR__"tingzi",
                "east"  : __DIR__"road1" ,       
        ]));
        set("item_desc", ([
                "diao" : HIW "\n這一對白雕正展翅欲飛。如果是桃花島"
                         "的弟子，騎上(" HIY "ride" HIW ")就\n可以"
                         "飛到中原，非常便利。\n\n" NOR,
        ]));
        set("objects", ([
                __DIR__"npc/shitong" : 2,
        ]));
        set("outdoors", "taohua");
        setup();
}

void init()
{
            add_action("do_ride", "ride");
}

int do_ride(string arg)
{
            object ob = this_player();

        if (! arg || arg != "diao" )
                return notify_fail("你要騎什麼？\n");

        if ((int)query("sb_ride"))
                return notify_fail("現在白雕已經被人騎走了，等會兒再來吧。\n" ) ;

        if( query("family/family_name", ob) != "桃花島" )
        {
                      message_vision(HIW "\n$N" HIW "一躍身跨上了白雕。只見白雕"
                               "仰天長唳，突然猛然一顛……\n" HIR "結果$N"
                               HIR "摔了個鼻青臉腫，看來白雕對$N" HIR "並"
                               "不太感興趣。\n" NOR, ob);
                      return 1;
            }

            addn("sb_ride", 1);
            message_vision(HIW "\n$N" HIW "一躍身跨上了白雕。只見白雕仰天長唳"
                       "，突然展翅高飛。但\n看一雕一人身形漸漸縮小，終至不"
                       "見。\n\n" NOR, ob);

            ob->move("/d/taohua/lantian") ;
            tell_object(ob, HIW "\n你不斷地飛呀飛，萬水千山身下飄過……\n\n" NOR);
            call_out("taohua", 1, ob);
            return 1;
}

void taohua(object ob)
{
        if (base_name(environment(ob)) != "/d/taohua/lantian")
                return;
          ob->move("/d/guiyun/qianyuan");
          tell_object(ob, HIC "\n你終於飛到了中原，白雕落了下來。\n\n" NOR);
            addn("sb_ride", -1);
}