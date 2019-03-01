// /yubifeng/fengdi.c
// Last modified by winder 2003.9.2

int do_climb(string arg);

inherit ROOM;

void create()
{
        set("short", "玉筆峰下");
        set("long", @long
這座鬆林好長，走了半個時辰方始過完，一出鬆林，即到一座山峰
腳下。山峰(feng)雖非奇高，但宛如一根筆管般豎立在群山之中，陡削
異常，壁立千仞，非同小可。莫說是人，即令猿猴也是不易上去。        
long );
        set("exits", ([
                "west" : __DIR__"songlin5",
        ]));
        set("item_desc", ([
                "feng" : "山峰覆蓋堅冰，光潔晶瑩，滑不留手，難以攀爬。\n",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "yubifeng");
        set("coor/x", 6110);
        set("coor/y", 5170);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_climb","climb");
        add_action("do_climb","pa");
}

int do_climb(string arg)
{
        object me = this_player();
        int n;

        n = me->query_skill("dodge", 1);

        if ( !arg || arg != "feng")
        {
                write("你要爬什麼呀？\n");
                return 1;
        }
        message_vision("$N深吸了一口氣，運起壁虎遊牆功，沿著崖壁向上爬。\n",me);
        if( n>140 && query("qi", me)>1400 )
        {
                message_vision("\n .... \n\n .... \n\n$N爬了半天，終于爬了上來，$N不禁站在峰頂，俯視群峰，長長出了一口氣。\n\n", me);
                me->move(__DIR__"fengding");
        }
        else
        {
                message_vision("$N爬了一會，太累了，無奈滑了下來。\n", me);
                me->receive_damage("qi",15);
                me->receive_wound("qi",10);
        }
        return 1;
}