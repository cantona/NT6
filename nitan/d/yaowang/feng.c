inherit ROOM;

void create()
{
        set("short", "山峯");
        set("long", @LONG
這裏是一處光禿禿的山峯，由南面向下望去，氣勢恢宏的藥王谷
盡收眼底，邊上十幾丈高的陡峭石壁。西面有一塊石頭絞盤，
盤上拴着一根胳膊粗的[繩子]垂向下面。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "southdown" : __DIR__"shangpo5",
]));

        set("item_desc", ([
        "繩子" : "這是一根胳膊粗繩子，看樣子是攀(climb)着上下山峯用的。\n",
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

        if(find_call_out("arrive_down") != -1)
                return notify_fail("有人正在攀着繩子向下爬呢，等一會兒。\n");

        me->start_busy(3);
        message_vision("$N攀着繩子緩緩的向下爬去。\n", me);
        call_out("arrive_down", 2, me);

        return 1;
}

protected void arrive_down(object who)
{
        if(!who || (environment(who) != this_object()))
                return;

        who->move(__DIR__"fengdown1");
}
