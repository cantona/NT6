// Room: /d/shaolin/putiyuan.c
// by Doing Lu 10/10/2K

// 迷題：取易筋經
// 掀“一夢如是”
// xian 一
// xian 夢
// xian 如 3 (因為如有多個，掀第三個)
// xian 是
// 然後look hole可以看到書，get book from hole即可。

#define THE_BOOK            "/clone/book/yijinjing"

inherit ROOM;

string look_hole();
string look_jing();
int do_xian(string arg);
int do_get(string arg);
void close_hole();

void create()
{
        set("short", "菩提院");

        set("long", @LONG
這裡是少林寺的菩提院。殿上並列這三尊銅像，佛像之前安著一
座屏風，屏風上裝著一面極大的銅鏡，擦得晶光凈亮，鏡中將你的人
影照了出來，銅鏡(jing)上鐫著四句經偈，佛像前點著幾盞油燈，昏
黃的燈光之下，依稀看到的是：『一切有為法，如夢幻泡影，如露亦
如電，當作如是觀。』
LONG );
        set("exits", ([
                "southdown" : __DIR__"guangchang4",
        ]));

        set("item_desc", ([
                "銅鏡" : (: look_jing :),
                "jing" : (: look_jing :),
                "hole" : (: look_hole :)
        ]));

        set("objects", ([
                CLASS_D("shaolin") + "/xuan-ji" : 1
        ]));

        set("valid_startroom", 1);
        set("book_count", 1);
        set("status", 0);
        setup();
}

void init()
{
        add_action("do_get", "get");
        add_action("do_xian", "xian");
}

string look_jing()
{
        object me;

        me = this_player();
        if( query("score", me)<1000 )
                return "你看了半天，只看到自己的影子，沒發現什麼。\n";

        if( query("score", me)<5000 )
                return "你覺得上面鐫的經偈似乎有些不同。\n";

        return "你發現上面鐫的經偈光澤和別處不一樣，難道可以掀(xian)開？\n";
}

string look_hole()
{
        string msg;

        if (query("status") != 4)
                return "哪裡有什麼洞？抓老鼠麼？\n";

        if (query("book_count"))
                return "這是銅鏡下面的一個小洞，裡面放著一本殘破的舊經書(book)。\n";

        return "這是銅鏡下面的一個小洞，裡面空空如也，什麼也沒有。\n";
}

int do_xian(string arg)
{
        int n;
        int right;
        object ob;

        if (! arg)
                return notify_fail("你要掀什麼字？\n");

        if (objectp(ob = present("xuanji dashi", this_object())) &&
            living(ob))
                return notify_fail("玄寂一眼掃了過來，冷冰冰"
                                   "的似要將你看穿，你哪敢亂動？\n");

        if (arg == "如")
                return notify_fail("你要掀哪一個如？\n");

        if (sscanf(arg, "%s %d", arg, n) != 2) n = 1;
        if (sizeof(arg) != 2)
                return notify_fail("經偈中沒有這個字呀！\n");

        if (strsrch("一切有為法如夢幻泡影如露亦如電當作如是觀", arg) == -1)
                return notify_fail("經偈中沒有這個字呀！\n");

        if (arg != "如" && n != 1 || n > 4)
                return notify_fail("經偈中沒有這沒多的“" +
                                   arg + "”字呀！\n");

        message_vision("$N掀了一下" + (n > 1 ? "第" + chinese_number(n) + "個" : "") +
                       "“" + arg + "”字。\n", this_player());

        right = 0;
        switch (query("status"))
        {
        case 1:
                if (arg == "夢") right = 2;
                break;
        case 2:
                if (arg == "如" && n == 3) right = 3;
                break;
        case 3:
                if (arg == "是") right = 4;
                break;
        }

        // 只要掀“一”就還原
        if (arg == "一") right = 1;
        set("status", right);
        message("vision", "你聽到“□啦”一聲響聲，似乎"
                          "有什麼機關觸動了。\n", this_object());
        if (right == 4)
        {
                message_vision("$N的手指還沒有離開鏡面，只聽得軋軋聲響，銅鏡已"
                               "經緩緩翻起，露出一個小洞(hole)。\n",
                               this_player());
                call_out("close_hole", 8);
        }
        return 1;
}

int do_get(string arg)
{
        object me;
        object ob;

        me = this_player();

        if (! arg)
                return 0;

        if (arg != "book from hole" &&
            arg != "book in hole" &&
            arg != "jing from hole" &&
            arg != "jing in hole")
                return 0;

        if (query("status") != 4)
                return 0;

        // 已經存在秘本，或者書已經被拿走
        if (objectp(ob = find_object(THE_BOOK)) &&
            environment(ob) || query("book_count") < 1)
        {
                write("你想書想暈了頭嗎？那裡並沒有什麼書呀！\n");
                return 1;
        }

        set("book_count", 0);
        ob = load_object(THE_BOOK);
        if (! objectp(ob))
        {
                write("系統出現故障 - 找不到應該在這裡的秘籍了 :)\n");
                return 1;
        }

        message_vision("$N從小洞中將那本經書取出，放進包內。\n", me);
        ob->move(me, 1);
        CHANNEL_D->do_channel(this_object(), "rumor",
                              me->name(1) + "從少林寺竊走一本易筋經。");
        return 1;
}

void close_hole()
{
        set("status", 0);
        message("vision", "一陣軋軋聲過後，銅鏡又緩緩的落下。\n",
                this_object());
}