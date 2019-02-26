// Room: /heizhao/xiaowu.c
// Date: Dec. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "小屋");
        set("long", @LONG
你快步走近瀑布，只見柳樹下那人頭戴斗笠，身披蓑衣，坐在
一塊石上，正自垂釣。這瀑布水勢湍急異常，一瀉如注，水中哪裏
有魚？縱然有魚，又哪有餘暇吞餌？看那人時，見他雙目一動不動
的凝視水中。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "out"   : __DIR__"pubu",
                "north" : __DIR__"pububian",
        ]));
        set("coor/x", -5020);
        set("coor/y", -1270);
        set("coor/z", 20);
        setup();
}

void init()
{
        object ob = this_player();
        if( !query_temp("yu_allow", ob) )
        {
message_vision("\n點蒼漁隱看到$N闖進屋去，釣竿一伸，把$N拖了出來！\n\n", ob);
                message("vision","只聽“呀”地一聲，"+query("name", ob)+
                "從小屋裏飛了出來，摔在地上。\n", environment(ob), ob);
                ob->move(__DIR__"pubu");
                return;
        }
}