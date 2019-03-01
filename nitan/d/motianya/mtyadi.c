// mtyadi.c 崖底

inherit ROOM;

int do_climb(string arg);

void create()
{
        set("short", "崖底");
        set("long", @LONG
你的面前是一座比直的山峰，高若千丈，峰頂在雲霧中隱約可見，
山峰光禿禿的，更無置手足處，山峰垂下一條鐵鏈(lian)，仔細一看，
鐵鏈並無鏽跡，似乎有人用它爬(climb)上爬下。
LONG );
        set("outdoors", "motianya");
        set("exits", ([
                "north" : __DIR__"mtroad",
        ]));
        setup();
}

void init()
{
        add_action("do_climb","climb");
}

int do_climb(string arg)
{
        int n;
        object me;

        if (arg != "lian")
        {
                write("你要爬什麼呀? \n");
                return 1;
        }

        me = this_player();
        n = me->query_skill("dodge", 1);
        message_vision("$N深吸了一口氣，慢慢沿著鐵鏈的向上爬。\n", me);
        if (n > 80)
        {
                message_vision("$N爬了半天，終于爬了上去，$N高興的"
                               "抹了抹汗。\n", me);
                me->move(__DIR__"mtdating");
        } else
        {
                message_vision("$N爬了一會，一不小心摔了下來。\n", me);
                me->receive_damage("qi", 50);
                me->receive_wound("qi", 50);
        }

        return 1;
}