// laofang.c

inherit ROOM;

void create()
{
        set("short", "牢房");
        set("long", @LONG
這裏有一張鐵牀，上面還依稀有一個人(man)，似乎被鐵鐐鎖着，
躺在那裏一動不動。
LONG );
        set("exits", ([ /* sizeof() == 2 */
            "south" : __DIR__"didao7",
        ]));

        set("item_desc", ([
                "man": "這個人如同稀泥一般，雙目渙散，沒有一點神采。整個人似乎只剩下
了一個乾枯的軀殼，然而卻還有一口氣，如果不是鐵鐐鎖着，也許可
以把他搬下牀來。\n",
        ]));
        setup();
}

void init()
{
        add_action("do_move", "move");
        add_action("do_move", "ban");
}

int do_move(string arg)
{
        object me;
        object ob;

        if (arg != "man")
                return notify_fail("你要搬什麼？\n");

        me = this_player();
        if( query_temp("get_xxbook", me) )
                return notify_fail("你沒興趣理這個半死不活"
                                   "的人，現在只想快點離開這裏。\n");

        if (query("get_book"))
        {
                write("你走上前去，卻發現鎖人的鐵鐐上面有一個細細的缺口，而且看上
去前不久有人曾經扭開過，你不禁有些迷惑，不知道有什麼機關，
索性就不再理牀上那人。\n");
                return 1;
        }

        write("你仔細看了看鐵鐐，發現它雖然是精鋼製成，卻有一個細細的缺口，
這種東西也能鎖住人？你不禁啞然失笑，隨即把那個奄奄一息的人
搬了下來，這是你突然發現原來牀上刻着一些字，你不禁有些疑惑。
於是將它抄了下來，準備慢慢研究，隨即想了想，用力將上面刻的
字抹去，然後把那個人重新放到牀上，不再理會。\n");
        set_temp("get_xxbook", 1, me);
        set("get_book", 1);

        ob = new("/clone/book/xx-book");
        ob->move(me, 1);

        return 1;
}