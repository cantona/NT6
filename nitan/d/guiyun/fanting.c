// Room: /d/guiyun/fanting.c
// Last Modified by winder on Jul. 9 2001

#include <ansi.h>
inherit ROOM;

int do_sit(string arg);
int do_stand();
void delete_served(object me);

void create()
{
        set("short", "飯廳");
        set("long", @LONG
這是歸雲莊弟子們每日吃飯的地方，飯菜的香味充溢著整個房間。
屋裡擺著一張大桌子(table)和一些椅子(chair)。屋中站著幾個僕役。
LONG
        );
        set("exits", ([
                "east"  : __DIR__"chufang",
                "west"  : __DIR__"chafang",
                "north" : __DIR__"lianwuchang",
        ]));
        set("item_desc", ([
                "table" : "一張大八仙桌，上面放著一些碗、盤、筷、勺等器具。\n",
                "chair" : "竹制的坐椅，看上去有些搖搖晃晃。\n",
        ]));
        set("no_fight", 1);
        set("coor/x", 250);
        set("coor/y", -870);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_stand", "stand");
        add_action("do_stand", "zhan");
        add_action("do_sit", "sit");
        add_action("do_sit", "zuo");
}

int serve_food(object me)
{
        if (!present(me, this_object())) return 0;
        message_vision("僕役走過來，給$N端來了一碗米飯。\n", me);
        
        new(__DIR__"obj/mifan")->move(me);

        set_temp("marks/food_served", 1, me);
        call_out("delete_served", 120, me);
        return 1;
}

void delete_served(object me)
{
        if( objectp(me))delete_temp("marks/food_served", me);
}

int do_sit(string arg)
{
        object me = this_player();
        mixed *local;

        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙著呢！\n");
        if (arg == "table" || arg == "zhuozi")
                return notify_fail("你要坐在桌子上？那先把你煮熟了再端上來吧。\n");        

        if ( !arg || (arg != "chair" && arg != "yizi") )
                return notify_fail("你要坐在地板上？有個性！可惜的是這會影響歸雲莊的形象。\n");        
        if( query_temp("marks/sit", me) )
                return notify_fail("你已經坐在座位上了。\n");        
        message_vision("$N找了個空位座下，等著吃飯。\n", me);        
        local = localtime(time() * 60);
        if (local[2] < 6) {
                message_vision("僕役走過來對$N說：大半夜的您讓小的去哪裡弄吃的啊？\n", me);
                message_vision("$N無奈地又站了起來。\n", me);        
                return notify_fail("");
        }
        else if (local[2] > 8 && local[2] < 11) {
                message_vision("僕役走過來對$N說：過了早飯時間啦，中午再來吧。\n", me);
                message_vision("$N無奈地又站了起來。\n", me);        
                return notify_fail("");
        }
        else if (local[2] > 13 && local[2] < 17) {
                message_vision("僕役走過來對$N說：過了午飯時間啦，晚上再來吧。\n", me);
                message_vision("$N無奈地又站了起來。\n", me);        
                return notify_fail("");
        }
        else if (local[2] > 20) {
                message_vision("僕役走過來對$N說：過了晚飯時間啦，您就忍一宿吧。\n", me);
                message_vision("$N無奈地又站了起來。\n", me);        
                return notify_fail("");
        }
        if( query_temp("marks/food_served", me)){
                message_vision("僕役走過來對$N說：吃飽了的就出去吧，別佔著地方！\n", me);
                message_vision("$N發覺眾人的眼光都在盯著自己，忙站起身來，尷尬地說：我只是試試這椅子結實不結實。\n", me);
                return notify_fail("");
        }
        set_temp("marks/sit", 1, me);

        call_out("serve_food", 1, me);
        return 1;
}

int do_stand()
{
        object me = this_player();

        if( !query_temp("marks/sit", me) )
                return notify_fail("你已經站著了，是不是站久了有點發昏啊？\n");        
                        
        message_vision("$N拍拍屁股，站了起來。\n", me);        
        delete_temp("marks/sit", me);
        return 1;
}

int valid_leave(object me, string dir)
{
        if( query_temp("marks/sit", me) )
                return notify_fail("你打算連椅子也搬出去？\n");        

        if ((dir == "north") && present("dami fan", me))
//        if (random(3)) 
                return notify_fail("僕役跑過來說：沒吃完的也別帶走啊，考慮一下別人嘛。\n");
        
        return ::valid_leave(me, dir);
}