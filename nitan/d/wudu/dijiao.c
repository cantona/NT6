inherit ROOM;

void create()
{
        set("short", "地窖");
        set("long", @LONG
這是一個陰暗的地窖，頭頂被一張草席(xi)擋住了光線。地窖裡
存放著一些準備過冬的食物，都整齊的堆放在木板上。
LONG);
        set("objects", ([
                __DIR__"obj/shibing": 2,
                __DIR__"obj/huluobu": 1,
                __DIR__"obj/tudou": 1,
        ]));
        set("item_desc", ([
                "xi" : "\n一張厚厚的草席蓋在洞口，遮住了外面的陽光。\n" ,
        ]));

        setup();
}

void init()
{
        add_action("do_move", "pull");
}

int do_move(string arg)
{
        object me,hole;
        string dir;

        me = this_player();
        if (! arg || arg == "") return 0;
        if (arg == "xi")
        {
                message_vision("\n$N掀開蓋在洞口的草席爬了上去。\n", this_player());
                me->move(__DIR__"minju10");
                message_vision("\n蓋在地上的草席忽然一掀，$N從下面鑽了出來。\n",me);
        } else
        {
                message_vision("\n$N雙手在空中比劃了幾下，但似乎什麼也沒抓住。\n", this_player());
        }               
        return 1;
}