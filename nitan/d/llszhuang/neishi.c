#include <ansi.h>
inherit ROOM;
string look_book();
void create()
{
        set("short","棲霞館");
        set("long",
"這裡是日常起居的地方，收拾得一塵不染，而且頗為雅致，據說這裡\n"
"的莊主頗愛習武，看看牆上掛著的毒藥囊和刀槍就可以知道。靠窗的地方\n"
"是一個梳妝台，鏡子前面是一本翻開的書(Book)。還有一個奇形怪狀的輪\n"
"盤放在旁邊，也許是什麼古怪機關。\n"
);
        set("no_magic", "1");

        set("exits", ([ /* sizeof() == 2 */
          "south" : __DIR__"hall",
        ]));
        set("seed1",random(10)+1);
        set("seed2",random(20)+21);
        set("seed3",random(50)+51);
        set("seed4",random(100)+101);

      set("item_desc", ([
                "book": (: look_book :),
        ]) );

        setup();
}

int init()
{
        add_action("do_turn","turn");
}

string look_book()
{
        string result;
        object me;
        int puzzle;

        me = this_player();
        result = "\n這本書上沒有什麼值得注意的東西。\n";
        if( puzzle=query_temp("marks/xanadu_hall2", me) )
        {
                set_temp("marks/xanadu_hall3", 1, me);
              result += "就在你失望地要放下書的時候，裡面掉出來一張字條，上面寫到: \n"
                          "撥動輪盤就有一道門可以進去。\n";
                result += "對了，還有，輪盤的數字嘛，要考考你...\n";
                result += "這個數，它除"+query("seed1")+"余"+puzzle%query("seed1")+"，";
                result += "它除"+query("seed2")+"余"+puzzle%query("seed2")+"，";
                result += "它除"+query("seed3")+"余"+puzzle%query("seed3")+"，";
                result += "它除"+query("seed4")+"余"+puzzle%query("seed4")+"\n";
                result += "然後試一下(turn)你猜到的數字，看看有什麼發現。\n";
        }
        return result;
}

int do_turn(string arg)
{
        object me;
        int answer,puzzle;

        me = this_player();
        if(!arg)
                return notify_fail("你要把輪盤轉到哪一個數字上？\n");
        if( query("neili", me)<500 )
                return notify_fail("你的內力不夠，撥不動輪盤。\n");
            if( !(answer = (int)arg) || !(query_temp("marks/xanadu_hall3", me)) ) 
              return notify_fail("你瞎轉什麼？\n");
        addn("force", -150, me);
        message_vision("$N把輪盤撥到了"+arg+"的位置\n",me);
        puzzle=query_temp("marks/xanadu_hall2", me);
        if( ("X"+puzzle+"X") == ("X"+answer+"X") )
        {
                write("一陣機關之聲響過之後，你來到了一個新的地方。\n");
                delete_temp("marks/xanadu_hall2", me);
                delete_temp("marks/xanadu_hall3", me);
                me->move(__DIR__"lou0");
                tell_room(this_object(),"牆上突然開了一道門，"+query("name", me )
+"毫不猶豫地走了進去。\n");
        }
        else
                message_vision("可是什麼都沒有發生。\n",me);
        return 1;
}
