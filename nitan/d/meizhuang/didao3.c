// didao3.c

inherit ROOM;

void close_path();

void create()
{
        set("short", "梅莊密道");
        set("long", @LONG
這是一條昏暗潮濕的地道，地道很長，兩邊點着兩根不太明亮的
火把，地道兩旁的牆壁上畫着很多不知道出自何人之手的壁畫，而且
畫得相當難看，你加快腳步，想知道地道的盡頭是什麼地方。突然之
間你發現這裏的地面已經是木板(floor)拼成的了。
LONG );
        set("exits", ([
            "south" : __DIR__"didao2",
        ]));
        set("item_desc", ([
                "floor": "這層木板似乎可以拉開(pull)。\n",
        ]));

        setup();
}
void init()
{
        add_action("do_open", "pull");
}

int do_open(string arg)
{
        object obj;
        object me;

        if (! arg || arg == "")
        {
                write("你要打開什麼？\n");
                return 1;
        }

        if (arg == "floor")
        {
                me = this_player();
                if (! query("exits/down"))
                {
                        set("exits/down", __DIR__"didao4");
                        call_out("close_path", 5);
                } else
                {
                        write("地上的木板現在已經拉開了。\n");
                        return 1;
                }

                message_vision("$N拉起地上的木板，發現下面是空的。\n", me);
                return 1;
        } else
        {
                write("你沒法打開 " + arg + " 這樣東西。\n");
                return 1;
        }
}

void close_path()
{
        if (! query("exits/down")) return;
        message("vision", "木板又彈了回來，遮住了下面的密道。\n",
                this_object());
        delete("exits/down");
}