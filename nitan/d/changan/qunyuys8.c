//Room: qunyuys8.c

inherit ROOM;

void close_path();

void create()
{
        set("short", "羣玉樓雅室");
        set("long", @LONG
一間雅室。房中放着一張大牀，牀上鋪着繡花的錦被和枕頭。湘
繡馳名天下，大紅錦被上繡的是一對戲水鴛鴦，顏色燦爛，栩栩欲活。
几上點着一根紅燭，紅燭旁是一面明鏡，一隻梳粧箱子。牀前地下兩
對繡花拖鞋，一對男的，一對女的，並排而置。仔細看看你會發現這
個房間的牀有些怪異。
LONG );
        set("exits", ([ /* sizeof() == 1 */
                "west" : "/d/changan/qunyulou3",
        ]));
        set("objects", ([
                "/d/changan/npc/dashou" : 4,
        ]) );
        set("item_desc", ([
                "bed": "這張牀似乎可以推開(push)。\n",
                "牀" : "這張牀似乎可以推開(push)。\n",
                "大牀" : "這張牀似乎可以推開(push)。\n"
        ]) );

        set("coor/x", -10700);
	set("coor/y", 1950);
	set("coor/z", 20);
	setup();
}
void init()
{
        add_action("do_push", "push");
}

void close_path()
{
        if (! query("exits/enter")) return;
        message("vision","大牀又滑了回來，蓋住了暗格。\n",
                this_object());
        delete("exits/enter");
}

int do_push(string arg)
{
        object me;
        me = this_player();
        if (! arg || arg == "" ) return 0;
        if (arg == "bed" || arg == "牀" || arg == "大牀")
        {
                write("你用力推開一張大牀，");
                if ((int) me->query_str() >= 30)
                {
                        write("牀下露出了一個暗格。\n");
                        if (! query("exits/enter"))
                        {
                                     set("exits/enter", "/d/changan/qunyums");
                                call_out("close_path", 5);
                        }
                        return 1;        
                } else
                write("試着推了推後面的暗格，但沒有推開。\n");
                return 1;
        }
        return notify_fail("你要推開什麼？\n");
}

int valid_leave(object me, string dir)
{
        object ob;
        if (dir == "enter" &&
            objectp(ob = present("da shou", this_object())) &&
            living(ob))
        {
                message_vision("$N對$n喊道：那裏是羣玉樓的私人"
                       "地方，外人不要進去！\n", ob, me);
                write("糟糕！被發現了！\n");
                ob->kill_ob(me);
                me->fight_ob(ob);       
                return -1;
        }

        return 1;
}