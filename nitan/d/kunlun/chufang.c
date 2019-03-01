// Room: /d/kunlun/chufang.c
// Last Modified by winder on Nov. 14 2000

#include <ansi.h>
inherit ROOM;

void init();
int do_tap(string arg);
int do_sit(string arg);
void delete_served(object me);

void create()
{
        set("short", "廚房");
        set("long", @LONG
這裡是昆侖弟子用餐的地方。由于天長日久，牆壁都被煙熏黑了。
屋裡擺著幾張桌椅，幾位昆侖弟子正在大吃大喝，行酒猜拳。
LONG );
        set("exits", ([
                "east" : __DIR__"jiuqulang7",
        ]));
        set("objects",([
                __DIR__"npc/puren" : 1,
                __DIR__"obj/rice" : 2,
                __DIR__"obj/baozi" : 2,
                __DIR__"obj/xiangcha" : 1,
                __DIR__"obj/kaoya" : 1,
        ]));
        set("no_fight", 1);
        set("coor/x", -120010);
        set("coor/y", 40100);
        set("coor/z", 90);
        setup();
}

void init()
{
        add_action("do_tap", "tap");
        add_action("do_tap", "knock");
        add_action("do_sit", "sit");
}

int do_tap(string arg)
{

        object me;
        object cui;

        if (!arg || (arg != "desk" && arg != "table"))
        {
                return notify_fail("你要敲什麼？\n");
        }

        me = this_player();
        if( !objectp(cui = present("pu ren", environment(me))) )
                return notify_fail("你敲了敲桌子，卻還是沒人理你。你突然感覺自己很無聊。\n");

        if( !query_temp("marks/sit", me) )
                return notify_fail("你敲了敲桌子，卻沒想到有對年輕人從桌底下鑽出來，愕然地看著你，"
                        +"\n你突然感覺自己很愚蠢。\n");

         if( query_temp("marks/served", me) )
         {
                  message_vision("僕人不耐煩地對$N說道：剛給你上過茶你接著就要，"+
                                "你不累可我累啊！\n", me);
                  return notify_fail("");
         }

        message_vision("$N端坐在桌前，輕輕扣了下桌面，僕人連忙過來招呼。\n", me);

        cui->serve_tea(me) ;

         set_temp("marks/served", 1, me);
//  remove_call_out("delete_served");
         call_out("delete_served", 10, me);

        return 1;
}


void delete_served(object me)
{
        if( objectp(me))delete_temp("marks/served", me);
}


int do_sit(string arg)
{

        if ( !arg || (arg != "chair") )
                return notify_fail("你要坐什麼上面？\n");

        if( query_temp("marks/sit", this_player()) )
                return notify_fail("你已經有了個座位了。\n");

        set_temp("marks/sit", 1, this_player());
        return notify_fail("你找了個空位座下，等著上茶。\n");
}


int valid_leave(object me, string dir)
{

        if ( (dir == "west" || dir == "northwest" )
                && ( present("xiang cha", this_player())
                || present("ci wan", this_player())
                || present("kaoya", this_player()) 
                || present("rice", this_player()) )
                && objectp(present("pu ren", environment(me))) )
        switch ( random(2) )
        {
        case 0:
                message_vision("僕人伸手攔住了$N：還是先把東西吃完了再走吧。",me);
                return notify_fail("\n");
                break;
        case 1:
                message_vision("僕人攔住$N道：何掌門吩咐，飲食不得帶出茶房。",me);
                return notify_fail("\n");
                break;
        }

        delete_temp("marks/sit", me);
        delete_temp("tea_cup", me);
        return ::valid_leave(me, dir);
}