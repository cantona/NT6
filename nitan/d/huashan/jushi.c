// jushi.c

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "居室");
        set("long", @LONG
這裡是岳夫人的寢室，岳夫人在江湖上人稱「淑女劍」，為人極
有骨氣，她的居室卻相當樸素，床椅之外，靠窗(window)處有個梳妝
台(tai)，牆上掛著一口寶劍(sword)， 蛇皮吞口看來很是鋒利。
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "east" : __DIR__"changlang",
        ]));

        set("objects", ([
            CLASS_D("huashan") + "/yue-wife" :1,
        ]));

        set("item_desc", ([
                "window" : "窗外就是天聲峽了。往外望去，雲深谷幽令人目眩。\n",
                "sword"  : "這是上次前往福建時帶回的龍泉劍。\n",
                "tai"    : "這是一張紅漆梳妝台，半開的抽屜斜插著幾朵鮮花。\n"
        ]));

        setup();
}
void init()
{
        add_action("do_move", "push");
        add_action("do_move", "move");
        add_action("do_pick", "pick");
        add_action("do_pick", "zhai");
}

int do_move(string arg)
{
        object yue;
        object paper, me = this_player();

        if (arg != "tai")
                return 0;

        yue = present("yue wife", environment(me));
        if (! objectp(yue) || ! living(yue))
                return 0;

        if( query("family/master_id", me) != query("id", yue) )
        {
                write("岳夫人喝道：這位" +
                      RANK_D->query_respect(me) +
                      "，你不能隨便翻人家東西。\n");
                return 1;
        }

        if( query("combat_exp", me)<20000 )
        {
                write("岳夫人看了看你，皺眉道：“你好好給我"
                      "練功去，瞎翻什麼？”\n");
                return 1;
        }

        if (! query("had_yunu"))
        {
                message_vision("$N輕輕的拉開抽屜，發現裡面有一"
                               "本書...。\n", me);
                paper = new("/clone/book/yunu_book");
                paper->move(__FILE__);
                set("had_yunu", 1);
                return 1;
        }

        message_vision("$N輕輕的拉開抽屜，可是裡面啥都"
                       "沒有...\n", me);
        return 1;
}

int do_pick(string arg)
{
        object sword;
        object yue;
        object me = this_player();

        if (arg != "sword")
                return 0;

        yue = present("yue wife", environment(me));
        if (! objectp(yue) || ! living(yue))
                return 0;

        if( query("family/master_id", me) != query("id", yue) )
        {
                write("岳夫人喝道：這位" + RANK_D->query_respect(me) +
                      "，你不能隨便翻人家東西。\n");
                return 1;
        }

        if( query("combat_exp", me)<20000 )
        {
                write("岳夫人看了看你，皺眉道：“你好好給我"
                      "練功去，亂動什麼？”\n");
                return 1;
        }

        if (! query("had_sword"))
        {
                message_vision("$N輕輕的摘下寶劍，哈哈，真"
                               "開心...\n", me);
                sword = new(__DIR__"obj/longquan");
                sword->move(me, 1);
                set("had_sword", 1);
                return 1;
        }

        message_vision("$N伸手去摘寶劍，才發現只剩劍鞘了，寶劍早就"
                       "被別人取走了...。\n", me);
        return 1;
}

void reset()
{
        ::reset();
        delete("had_sword");
        delete("has_yunu");
}