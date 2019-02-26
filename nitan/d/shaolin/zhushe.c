// Room: /d/shaolin/zhushe.c
// Date: YZC 96/01/19
// Dat:  Cleansword 96/02/20

inherit ROOM;

int do_remove();
void fainting(object me, object ob);
string look_stone();

/* (move stone) 豬舍石塊下埋着奄奄一息的喬三槐。告訴你
金剛伏魔圈前半段的走法(western)，説完頭一歪，死了。如玩家
學過內功，可用所學內功中(life heal)之法延續喬三槐一口氣，
令其説出後半段走法(news)，並且告知出迷宮走法藏在廚房某處，
未及説完何處就死了。玩家自己找出何處（灶頭裏，可以鑽進去，
裏面有一塊磚，上刻出迷宮走法）。*/

void create()
{
        set("short", "豬舍");
        set("long", @LONG
這是間破爛的農家豬舍。圈裏養着幾頭瘦豬，泔槽已經乾涸了，
草料也開始發黴腐爛。由於好多天沒人清理牲口的糞便，滿屋子瀰漫
着一股惡臭。屋角堆了一大堆石塊(stone)，足有半人高。
LONG );
        set("exits", ([
                "southeast" : __DIR__"houshan",
        ]));
        set("item_desc",([
                "stone"                :        (: look_stone :),
        ]));
        set_temp("available", 1);
        setup();
}

void init()
{
        add_action("do_move", "move");
}

int do_move(string arg)
{
        string dir;
        object me,ob;

        if( !arg || arg=="" || !query_temp("available") ) return 0;

        if( arg=="stone" && query_temp("available")) {
                write("你試著把石塊一塊塊地搬開，突然發現下面埋着個奄奄一息的老人 !\n\n");
                delete_temp("available");
        }


        me = new(__DIR__"npc/lao-qiao",1);
        me->move(__DIR__"zhushe");

        ob = this_player();        

        message_vision("老人斷斷續續地説道: 我是喬三槐，快...，快往北山上走...，
進了松林...，往南...，往東...，往西...，往東...，再往北......\n\n", ob);

        message_vision("喬三槐嘴脣動了動，似乎還想説些什麼，卻因傷重難支，昏死了過去。\n", ob);

        me->unconcious();

        remove_call_out("fainting");
        call_out("fainting", 20, me, ob);

        return 1;
}

void fainting(object me, object ob)
{
        if (! me || ! ob || environment(me) != this_object() ||
            environment(ob) != this_object())
                return;

        if( query("qi", me) <= 50 )
        {
                message_vision("喬三槐緩緩甦醒了過來，説道: 謝...謝......。\n",ob);
                me->die();
        }
        else
        {
                message_vision("\n喬三槐醒了過來，説道: 再往北，往東，往西，南......出路在磚......\n\n",ob);
                message_vision("説罷腦袋便軟軟地垂了下去......",ob);
                me->die();
        }

        return;
}

string look_stone()
{
        return "這是一大堆石塊，堆在牆腳邊，不知是派什麼用場。\n";
}