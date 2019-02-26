#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "虎穴深處");
        set("long", @LONG
這裏是森林裏巖洞的深處，幾隻剛生下幾個月的小虎崽正
在洞中嬉戲，你突然發現洞內角落裏有一堆白骨，你仔細一看
竟然是一具人類的遺骨。
LONG);

        set("exits", ([
                "north" : __DIR__"huxue1",
        ]));
        set("objects", ([
                "/clone/quarry/laohu" : 1,
        ]));
        set("item_desc", ([
                    "bone"  : "一具人類的遺骨，下面似乎壓着什麼東西，你可以仔細搜索(sousuo)一下。\n",
        ]) );

        setup();
}

void init()
{
        add_action("do_search", "search");
        add_action("do_search", "sousuo");
        add_action("do_train", "rain");

}

int do_search(string arg)
{
        object me = this_player();
        object ob; 
        if ((! arg) || ! ((arg == "bone") || (arg == "遺骨")))
                return notify_fail("你要搜索什麼？\n");

        message_vision(HIR "\n$N" HIR "輕輕撥動那堆白骨。\n\n" NOR, me);
 
        if(query("not_tongpai"))
        {
                message("vission", HIR "只聽呼啦一聲，從裏面竄出來一隻大老鼠。\n" NOR, me);
                return 1;
        }


        ob = new(__DIR__"obj/tongpai.c");
        ob->move(environment(me));
        message_vision(HIY "只聽“噹啷……”一聲，從裏面滾出來一面銅牌。\n\n\n" NOR, me);
        set("not_tongpai", 1);
        call_out("regenerate", 86400);
        return 1;
}

int regenerate()
{
        set("not_tongpai", 0);
        return 1;
} 
