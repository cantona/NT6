// baishulin4.c 柏樹林
// Winder Oct.10 1998

inherit ROOM;
int do_kan(string arg);

void create()
{
        set("short", "柏樹林");
        set("long", @LONG
這裡是樹林的邊緣，光線亮的多了。參天的柏樹也稀疏了很多。
旁邊有一叢灌木(frutex)雜生。灌木再往前，就是懸崖了。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "west" : __DIR__"baishulin3",
                "southdown" : __DIR__"baishulin2",
        ]));
        set("no_clean_up", 0);
        set("count",1);
        set("item_desc", ([
            "frutex": "一叢你叫不出名字的灌木，其中夾雜著很多小刺。\n"
        ]) );

        set("coor/x", -3130);
        set("coor/y", 40);
        set("coor/z", 40);
        setup();
}

void init()
{
        add_action("do_kan","kan");
}

int do_kan(string arg)
{
        object me=this_player();
        object weapon;
        object ob;

        if( !arg || arg != "frutex" ) {
                return notify_fail("你要砍什麼？\n");
        }

        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("不用家伙恐怕不行吧！\n");

        if (query("count")>0) {
        message_vision("$N拔出兵刃，走到灌木叢跟前一陣亂砍，把面前一些聳立的灌木\n",me);
        message_vision("砍倒以後，$N發覺下面生長著一棵什麼小草，于是順手拔了起來，\n", me);
        message_vision("沒想到這東西下面連著好大一塊根莖。\n",me);
        addn("count",-1);
        ob=new("/clone/medicine/vegetable/fuling");
        ob->move(me);
        }
        else {
        message_vision("$N拔出兵刃，走到灌木叢跟前一陣亂砍，把面前一些聳立的灌木\n",me);
        message_vision("砍倒了。$N累的夠嗆。\n", me);
        }

        return 1;
}