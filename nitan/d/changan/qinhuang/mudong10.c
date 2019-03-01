//mudong.c
// This is a room made by Wsl.
#include <room.h>
inherit ROOM;
int do_use(string arg);
int do_pull(string arg);
int do_enter(string arg);
void create()
{
        set("short", "墓穴");
        set("long", @LONG
你隱約看到四周的牆上插著六柄火把。
LONG );
        setup();
}
void init()
{
        add_action("do_use", "use");
        add_action("do_pull", "pull");
        add_action("do_enter", "enter");
}
int do_use(string arg)
{
        object me;
        me = this_player();
        if( !arg || arg=="" ) return 0;
        if (!present("fire",me)) return 0;
        if( arg=="fire" ) {
                remove_call_out("cls");
                call_out("cls", 30, this_object());
             write(
"你取出火折一晃，湊上前去點燃了其中的一只火把，也不知是什麼機關，
其它的五只火把一一燃了起來。但你發現這樣走下去好象永無盡頭，難道
真有機關嗎？\n");
        set("long", @LONG
洞內一片凌亂，各種盔甲兵刃散落在地上，洞壁上刻了各種各樣
的圖案，出口四通八達，也不知暗藏了什麼機關暗器。
LONG
        );
    set("item_desc", ([
"機關" : "在火把的照明下，你試著仔細觀察周圍的景象，但始終不能發現什麼異樣來。\n",
"火把" : "你看了看插在牆上的火把，這火把似乎......\n",
]));
        set("exits", ([
                "north" : __DIR__"mudong"+random(10),
                "south" : __DIR__"mudong"+random(10),
                "east" : __DIR__"mudong"+random(10),
                "west" : __DIR__"mudong"+random(10),
        ]));
        set_temp("dian", 1, me);
        return 1;
       }
        return notify_fail("你想點燃什麼？\n");
}
int do_pull(string arg)
{
    string p;
    p=sprintf("%d",query("passwd1", this_player()));
    if( !arg || arg == "" )
    if( !query_temp("dian", this_player()) )
    {
        write("什麼？！\n");
        return 1;
    }
    if( arg == p )
    {
        message_vision("$N只覺得一陣地動山搖。\n", this_player());
        message_vision("震動過後，在你腳下的一塊石板緩緩的移了開來。\n", this_player());
        set_temp("la1", 1, this_player());
        remove_call_out("close");
        call_out("close", 5, this_player());
        return 1;
    }
    else
    {
        write("你心中不斷祈禱，應該是這只吧！！！\n");
        if (random(6) != 4)
                {
            message_vision("$N拉下了其中的一只火把，這時，不知什麼地方突然射出一只毒箭，直射向你的腦門。\n", this_player());
            message_vision("$N急忙躲閃開去。但還是被利箭劃破了手臂。\n", this_player());
            set_temp("die_for", "被毒箭射", this_player());
            addn("qi", -30000, this_player());
            addn("eff_qi", -20000, this_player());
            return 1;
        }
        else
        {
            if( this_player()->query_skill("dodge",1)<1000 )
            message_vision("$N拉下了其中的一只火把，這時，不知什麼地方突然射出一只毒箭，直射向你的腦門。\n", this_player());
            message_vision("$N躲閃不及，毒箭從你的腦門對穿而過......\n",this_player());
            set_temp("die_for", "被毒箭射", this_player());
            this_player()->die();
            return 1;
        }
    }
}
int do_enter(string arg)
{
        object me;
        me = this_player();
        if( !arg || arg=="" ) return 0;
        if( !query_temp("la1", me))return 0;
        if( !query("passwd1", me))return 0;
        if( arg=="洞" ) {
             message_vision("$N戰戰兢兢的爬了進去。\n",me);
        me->move("/d/changan/qinhuang/mumen.c");
        delete_temp("dian", me);
        delete("passwd1", me);
        }       
          return 1;
}
void close(object me)
{
        message("vision","轟隆隆的響聲響過之後，石板又合上了。\n", this_object());
        delete_temp("la1", me);
}

void cls(object room)
{
        message("vision","不一會兒，火把就熄滅了。\n", room);
        set("long", @LONG
你隱約看到四周的牆上插著六柄火把。
LONG
);
        delete("item_desc");
        delete("exits", room);
}
