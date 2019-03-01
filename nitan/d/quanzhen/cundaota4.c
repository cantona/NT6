// cundaota4.c 存道塔頂
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

int do_dian(string arg);

void create()
{
        set("short", "存道塔頂");
        set("long", @LONG
這裡是存道塔的塔頂，塔梯到這裡就到了盡頭。牆壁上開著幾
個窗戶(window)，一個中年道人正捧著一本書苦苦研讀。天色昏暗，
桌上擺放著一支蠟燭(candle)，卻沒有點著。
LONG
        );
        set("exits", ([
                "eastdown" : __DIR__"cundaota3",
        ]));
        set("objects", ([
                __DIR__"npc/zhangjing" : 1,
        ]));

        set("item_desc", ([
        "window": "窗外白雲飄過，似乎你一伸手就可以抓住一片。\n",
        "candle": "一支普通的蠟燭，已經點的只剩一小半了。\n"
        ]) );

        set("count",1);
        set("coor/x", -2790);
        set("coor/y", 130);
        set("coor/z", 200);
        setup();
        //replace_program(ROOM);
}

void init()
{
        add_action("do_dian","dian");
}

int do_dian(string arg)
{
        object ob;
        object me=this_player();

        if (!arg || arg != "candle")
                return notify_fail("你要點燃什麼？\n");

        if ( query("count")>0 &&
        present("zhangjing", environment(me)) &&
        living(present("zhangjing", environment(me))) ) {
                message_vision(HIG"$N走上前去，打著火把蠟燭點燃，屋裡頓時亮堂了許多。\n"NOR,this_player());
                message_vision("掌經道長抬起頭，好象剛從沉思中恢復過來似的，道：天\n",this_player());
                message_vision("色已晚了嗎，唉，我讀這本道德經竟然連天色也忘記了。\n",this_player());
                message_vision("好，多謝這位"+RANK_D->query_respect(me)+"了，我身上這東西是掌藥師弟送給我\n",this_player());
                message_vision("的，也不知道有什麼用，現在送給你啦。\n",this_player());
                addn("count",-1);
                ob=new("/clone/medicine/vegetable/moyao");
                ob->move(me);
        }
        else {
                message_vision("$N走上前去，打著火把蠟燭點燃，屋裡頓時亮堂了許多。\n",this_player());
        }
        return 1;
}
