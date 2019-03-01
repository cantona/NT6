// Room: /d/shaolin/zhonglou1.c
// Date: YZC 96/01/19

#include <ansi.h>

inherit ROOM;

void close_passage();
string look_floor();
//int do_open();
int do_open(string arg);

void create()
{
        set("short", "鐘樓一層");
        set("long", @LONG
這裡是塔樓的底層，一縷縷陽光從牆上的花磚縫隙裡透射進來，
在青磚地上投下別致的光影，如同一格格棋盤相似。往上看，長長的
木樓梯盤繞而上，似乎永無盡頭。牆角，梯級都相當潔凈，看來經常
有僧人打掃。
LONG );
        set("exits", ([
                "up" : __DIR__"zhonglou2",
                "out" : __DIR__"zhonglou",
        ]));
        set("item_desc",([
                "floor"                :        (: look_floor :),
        ]));
        set("objects",([
                __DIR__"npc/saodi-seng" : 1,
        ]));
//        set("no_clean_up", 0);
        setup();
}


void init()
{
//        add_action("do_open", "open");
}

int do_open(string arg)
{
        object room, me;

        if( !arg || arg=="" )
                return 0;

        if( arg=="brick" && !present("blade", this_player()))
                return notify_fail("空手挖？ 恐怕不行吧！\n");

        if( arg=="brick" && !query("exits/down") )
        {
                message_vision( 
                "$N走到樓梯下，趴在地上，試著用戒刀伸進青磚縫裡，慢慢的撬著……\n"
                "等到青磚一塊塊地起了出來，地上露出一個大洞，幾排石階往下伸去，\n"
                "從這裡分明通向一個暗道。\n", this_player());

                set("exits/down", __DIR__"andao3");
                if( room = find_object(__DIR__"andao3") ) 
                {
                        set("exits/up", __FILE__, room);
                        message("vision", "天花板忽然發出軋軋的聲音，露出一個向上的階梯。\n",
                                room );
                }
                remove_call_out("close_passage");
                call_out("close_passage", 3);
                return 1;
        }
        return 0;
}

void close_passage()
{
        object man, room, *ob;
        int i;

        if( !query("exits/down") )
                return;

        message("vision", 
        "只聽乒地一聲響，鐘樓小門被推了開來，一群僧兵一湧而入。\n"
        "他們有的砌磚，有的拌漿，七手八腳地用磚塊把洞口封了起來，\n"
        "再在磚縫間澆入燒紅的鐵汁。\n", this_object() );

        man=new(__DIR__"npc/seng-bing3");
        man->move(this_object());
        man=new(__DIR__"npc/seng-bing3");
        man->move(this_object());
        man=new(__DIR__"npc/seng-bing3");
        man->move(this_object());
        man=new(__DIR__"npc/seng-bing3");
        man->move(this_object());

        ob = all_inventory(this_object());
        for(i=0; i<sizeof(ob); i++) {
                if( !living(ob[i]) || !userp(ob[i]) || ob[i]==man ) continue;
                if( userp(ob[i]) ) { 
                        man->set_leader(ob[i]);
                        man->kill_ob(ob[i]);
                        ob[i]->fight_ob(man);
                }
        }

        if( room = find_object(__DIR__"andao3") ) {
//                room->delete("exits/up");
                message("vision", 
        "只聽乒，乓幾聲巨響，接著幾滴滾燙的鐵水滴了下來。\n"
        "向上的洞口被人用磚塊嚴嚴實實地封了起來。\n", room );
        }
        delete("exits/down");
}

string look_floor()
{
        return
        "一片結實平整的青磚地面，只在樓梯下的一角處略顯凹凸不平。\n";
}