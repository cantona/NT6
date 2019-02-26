// xiaowu.c 小屋


inherit ROOM;

void create()
{
        set("short", "石室");
        set("long", @LONG
這裏是一個很小的石室，比之外面的任何一個都要小很多，室中
放着一些亂七八遭的傢俱，牆角邊還有一張破爛的小牀(bed) ，石室
內滿是灰塵，已經好久沒人來過了，你是不是走錯地方了呀。
LONG );
        set("exits", ([
              "north" : __DIR__"shibi",
        ]));
        set("item_desc", ([
              "bed" : "一張舒適得讓人立馬想睡的小牀。\n"
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3080);
        set("coor/y", -25010);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_move","move");
}
int do_move(string arg)
{
        object me;

        me=this_player();
        if(!arg || arg!="bed") return 0;
        message_vision("$N用力把小牀移開，發現裏面竟然有一條祕密通道！\n",me);
         me->move(__DIR__"midao1");
        tell_object(me,"接着是一陣轟隆隆的響聲，你定神一看，自己已經處身在祕密通
道中了。\n");
         return 1;
}