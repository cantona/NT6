inherit ROOM;

void create()
{
        set("short", "山崖下");
        set("long", @LONG
這裡是山谷的谷底，靜悄悄地沒有一點聲響。西面是陡峭的
山壁高聳入雲，山壁下面有一根胳膊粗的[繩子]從上面垂下來。
LONG
        );

        set("item_desc", ([
        "繩子" : "這是一根胳膊粗繩子，看樣子是攀(climb)著上下山峰用的。\n",
]));

        set("exits", ([
        "west" : __DIR__"fengdown2",
]));

        set("outdoors", "yaowang");
        setup();
}

void init()
{
        add_action("do_push", "climb");
}

int do_push(string arg)
{
        object me = this_player();

        if(arg != "繩子")
                return 0;

        if(find_call_out("arrive_up") != -1)
                return notify_fail("有人正在攀著繩子向上爬呢，等一會兒。\n");

        me->start_busy(3);
        message_vision("$N攀著繩子緩緩的向上爬去。\n", me);
        call_out("arrive_up", 2, me);

        return 1;
}

protected void arrive_up(object who)
{
        if(!who || (environment(who) != this_object()))
                return;

        who->move(__DIR__"feng");
}
