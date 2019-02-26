// muwu1.c
// Modified by Winder June.25 2000

inherit ROOM;
int do_move(string arg);

void create()
{
        set("short", "木屋");
        set("long", @LONG
這裏是一間不大的木頭屋子，但是麻雀雖小，五臟俱全，屋子中只
是疏疏落落地擺着一張桌子和幾張小凳，靠牆放着一個大櫃子(gui)，
所以也不顯得怎麼小。
LONG );
        set("exits", ([
                "north" : __DIR__"xiaodao5",
        ]));
         set("objects", ([
                CLASS_D("xiaoyao")+"/kanggl": 1,
        ]));
        set("item_desc", ([
                "gui"   : "一座挺破舊的高櫃。\n",
        ]));
        set("coor/x", 80);
        set("coor/y", -520);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_move","move");
}

int do_move(string arg)
{
        object me = this_player();

        if(!arg || arg!="gui") return 0;
        if (me->is_busy() || me->is_fighting()) return notify_fail("你正忙着呢。\n");
        if(me->query_skill("construction", 1) < 10)
                return notify_fail("你的土木機關還不夠精熟，沒法打開高櫃機關。\n");
        message_vision("$N用力把高櫃移開，發現裏面竟然有一條祕密通道！\n",me);
        me->move(__DIR__"midao3");
        tell_object(me,"接着是一陣轟隆隆的響聲，你定神一看，自己已經處身在祕密通道中了。\n");
        return 1; 
}
