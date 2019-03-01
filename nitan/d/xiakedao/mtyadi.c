// mtyadi.c 崖底

inherit ROOM;

int do_climb(string arg);
void create()
{
        set("short", "崖底");
        set("long", @TEXT
你的面前是一座比直的山峰，高若千丈，峰頂在雲霧中隱約可
見，山峰光禿禿的，更無置手足處，山峰垂下一條鐵鏈(lian)，仔
細一看，鐵鏈並無鏽跡，似乎有人用它爬上爬下.
TEXT );
        set("outdoors", "motianya");
        set("exits", ([
            "north" : __DIR__"mtroad",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -2100);
        set("coor/y", -1700);
        set("coor/z", 0);
        setup();
}
void init()
{
        add_action("do_climb","climb");
}

int do_climb(string arg)
{
        int n;
        n = this_player()->query_skill("dodge",1);
        if ( !arg || arg != "lian")
        {
            write("你要爬什麼呀? \n");
            return 1;
        }
message_vision("$N深吸了一口氣，慢慢沿著鐵鏈的向上爬。\n", this_player());
        if(n >80){
message_vision("$N爬了半天，終于爬了上去，$N高興的不禁跳了起來。\n", this_player());
            this_player()->move(__DIR__"mtdating");
        }
        else
        {
message_vision("$N爬了一會，一不小心摔了下來。\n", this_player());
            this_player()->receive_damage("qi",50);
            this_player()->receive_wound("qi",50);
        }
        return 1;
}