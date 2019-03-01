//RJQMENLOU3.C

inherit ROOM;

void create()
{
        set("short", "門樓三層");
        set("long", @LONG
這裡是一間大石室，中央擺放著石桌(zhuo)石椅(chair)，石桌上
刻有縱橫交錯的圖案，仔細看，原來是一棋局，棋盤上兩黑(heizi)、
一白(bai zi)，正該白方落子了。卻不知對弈的棋士為何沒有下完。
LONG );
        set("exits", ([
                "down" : __DIR__"rjqmenlou2",
        ]));
        setup();
}

void init()
{
        add_action("do_push", "push");
        add_action("do_sit", "sit");
}

int do_sit(string arg)
{

        if (arg != "chair")
                return notify_fail("你一下坐了個屁股墩。\n");

        if( query_temp("allsit", this_player()) == 1 )
                return notify_fail("你已經坐下了。\n");

        set_temp("allsit", 1, this_player());
        return notify_fail("你找了個空椅子座下，開始思考棋局。\n");
}

int do_push(string arg)
{
        object me;

        me = this_player();
        if (query_temp("allsit", me) != 1)
        {
                message_vision("$N只覺得一陣恍惚，倒在了地上。\n", me);
                delete_temp("hei", me);
                delete_temp("allsit", me);
                me->unconcious();
                return 1;
        }

        if (arg != "hei zi" && arg != "bai zi")
                return notify_fail("你輕輕按了一下石桌，真是一塊好玉呀！\n");

        if( query_temp("allsit", me) && (arg == "heizi") )
        {
                if (query_temp("hei", me)==2)
                {
                        delete_temp("hei", me);
                        write("你輕輕按了一下黑棋子，什麼反應也沒有。\n");
                        return 1;
                } else
                if (query_temp("hei", me)==1)
                {
                        set_temp("hei", 2, me);
                        write("你輕輕按了一下黑棋子，什麼反應也沒有。\n");
                        return 1;
                } else
                if (query_temp("hei", me)==0)
                {
                        set_temp("hei", 1, me);
                        write("你輕輕按了一下黑棋子，什麼反應也沒有。\n");
                        return 1;
                }
        }

        if (query_temp("allsit", me) && (arg=="bai zi"))
        {
                if(query_temp("hei", me)==2)
                {
                        message_vision("只見石椅猛的一沉，$N一聲慘叫，直"
                                       "跌到洞中去了。\n", me);
                        delete_temp("hei", me);
                        delete_temp("allsit", me);
                        me->move(__DIR__"rjqmidao");
                        return 1;
                }
                else
                {
                        write("你輕輕按了一下白棋子，什麼反應也沒有。\n");
                        return 1;
                }
        }
}

int valid_leave(object me, string dir)
{
            delete_temp("hei", me);
            delete_temp("allsit", me);
            return ::valid_leave(me, dir);
}
