// yaojishi.c 藥劑室
// Winder Oct.10 1998

inherit ROOM;
int do_pullout(string arg);

void create()
{
        set("short", "藥劑室");
        set("long", @LONG
這裡是全真教制藥、配藥的地方。這間房間本來很大，只是
被前後左右堆放的藥櫃藥箱擠的顯得小多了。藥櫃已經很陳舊了，
不過是用上好的南海沉香木做成的，據說用這種木材做成的櫃子
用來儲藏東西不會遭蟲蛀。藥櫃上面有個抽屜(drawer)。
LONG
        );
        set("sleep_room",1);
        set("exits", ([
                "east" : __DIR__"xianzhentang",
        ]));

        set("objects", ([
                __DIR__"npc/zhangyao" : 1,
        ]));

        set("item_desc", ([
        "drawer": "一個抽屜，不知道是因為粗心還是什麼原因，沒有上鎖。\n"
        ]) );

        set("count",1);
        set("coor/x", -2810);
        set("coor/y", 100);
        set("coor/z", 170);
        setup();
        //replace_program(ROOM);
}

void init()
{
        add_action("do_pullout","pullout");
}

int do_pullout(string arg)
{
        object me=this_player();
        object ob;

        if( !arg || arg != "drawer" ) {
                return notify_fail("你要拉開什麼？\n");
        }

        if (query("count")>0) {
        message_vision("$N趁著掌藥道長轉過身去，飛快地把抽屜拉開，裡面好象有什麼東西，\n",this_player());
        message_vision("還沒來得及看，掌藥道長又轉過身來。只嚇得$N一把抓起抽屜裡的東西\n", this_player());
        message_vision("塞進懷裡，然後裝作抬頭看藥櫃的木質，做出一副若無其事的樣子。哈\n",this_player());
        message_vision("哈，掌藥道長居然沒發覺，$N長出了一口氣，把無辜的表情收了回來。\n",this_player());
        addn("count",-1);
        ob=new("/clone/medicine/vegetable/tianqi");
        ob->move(me);
        }
        else {
        message_vision("$N趁著掌藥道長轉過身去，飛快地把抽屜拉開，裡面空空如也，原本在\n",this_player());
        message_vision("裡面的東西好象已經被人取走了。\n", this_player());
        }

        return 1;
}
