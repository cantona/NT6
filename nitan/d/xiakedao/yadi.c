// yadi.c 崖底

inherit ROOM;

int do_climb(string arg);
int do_swim(string arg);
int do_push(string arg);

void create()
{
        set("short", "崖底");
        set("long", @LONG
這就是懸崖谷底面了，出乎意料這是一個天然的湖泊，你現在在
湖底，四周全是水(water)，不時有幾條美麗的小魚從你身邊遊過，四
面並無明顯出口。
LONG );
        set("item_desc",([
            "water" : "碧綠碧綠的水，在陽光照耀下美麗級了，你不禁想遊泳了。\n",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3000);
        set("coor/y", -22070);
        set("coor/z", 0);
        setup();
}
void init()
{
        add_action("do_climb","climb");
        add_action("do_push","push");
        add_action("do_swim","swim");
}
int do_push(string arg)
{
        int n;
        n=query("neili", this_player());
        if( !arg || arg != "men")
        {
                write("你想推什麼呀? \n");
                return 1;
        }
        if( !query_temp("yadi_swim", this_player()) )
        {
                write("你想推什麼呀? \n");
                return 1;
        }
        else
                delete_temp("yadi_swim", this_player());

        message_vision("$N深深吸了一口氣，緊緊抓住石門的一側。\n", this_player());
        if (n >150)
        {
                message_vision("只見$N一運丹田氣，雙膀一使勁，石門竟緩緩的開了。\n", this_player());
                set("exits/west",__DIR__"shidong9");
                set("neili", n-150, this_player());
                remove_call_out("close");
                call_out("close",5, this_object());
        }
        else
        {
                message_vision("$N使盡了全身的力，石門卻紋絲沒動。\n", this_player());
                set("neili", 0, this_player());
        }
        return 1;
}

void close(object room)
{
        message("vision","石門自動的合上了。\n", room);
        delete("exits/west", room);
}

int do_swim(string arg)
{
        object me;
        me = this_player();
        if( !arg || arg != "water")
        {
                write("你想幹什麼呀?\n");
                return 1;
        }
        set_temp("yadi_swim", 1, this_player());
        message_vision("$N深吸了一口氣，奮力的遊了起來。\n", me);
        if( random(query("kar", me))>10 )
        {
                message_vision("你遊著遊著，突然發現了一道石門(men)，也許你能將它推(push)開。\n", me);
                me->receive_damage("qi", 15);
                me->receive_wound("qi", 10);
        }
        else
        {
                message_vision("你遊著遊著，突然發現了一條鐵索(suo)從上面伸了過來。這條鐵索並無鐵鏽，可能經常有人爬上爬下(climb)。\n", me);
                me->receive_damage("qi",10);
                me->receive_wound("qi",10);
        }
        return 1;
}

int do_climb(string arg)
{
        int n;
        n = this_player()->query_skill("dodge",1);
        if ( !arg || arg != "suo")
        {
                write("你要爬什麼呀? \n");
                return 1;
        }
        message_vision("$N深吸了一口氣，慢慢沿著鐵索的向上爬。\n", this_player());
        if(n >40)
        {
                message_vision("$N爬了半天，終于爬了上來，$N不禁在胸前雙掌合十，感謝佛祖。\n", this_player());
                this_player()->move(__DIR__"pubu");
        }
        else
        {
                message_vision("$N爬了一會，太累了，不小心滑了下來。唉!沒辦法了
，你認命吧。\n", this_player());
                this_player()->receive_damage("qi",15);
                this_player()->receive_wound("qi",10);
        }
        return 1;
}