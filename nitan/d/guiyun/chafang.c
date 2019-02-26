// Room: /d/guiyun/chafang.c
// Last Modified by winder on Jun. 29 2001

#include <ansi.h>
inherit ROOM;

int do_sit(string arg);
int do_stand();
void delete_served(object me);

void create()
{
        set("short", "茶房");
        set("long", @LONG
這是歸雲莊弟子們喝茶休息的地方，滿屋的茶香，沁人心脾。屋裏
擺着幾張桌子(table)和椅子(chair)，坐着幾個正在喝茶聊天的男女弟
子。屋中有幾個丫鬟正在忙着為大家上茶。
LONG );
        set("exits", ([
                "east" : __DIR__"fanting",
        ]));
        set("item_desc", ([
                "table" : "典雅的桃木小桌，上面放着水果盤和飲茶器具。\n",
                "chair" : "竹製的坐椅，看上去有些搖搖晃晃。\n",
        ]));
        set("no_fight", 1);
        set("coor/x", 240);
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

int serve_tea(object me)
{
        if (!present(me, this_object())) return 0;
        message_vision("丫鬟走過來，給$N端來了一杯茉莉花茶。\n", me);
        
        new(__DIR__"obj/huacha")->move(me);

        set_temp("marks/tea_served", 1, me);
        call_out("delete_served", 120, me);
        return 1;
}

void delete_served(object me)
{
        if( objectp(me))delete_temp("marks/tea_served", me);
}

int do_sit(string arg)
{
        object me = this_player();

        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙着呢！\n");
        if (arg == "table" || arg == "zhuozi")
                return notify_fail("你要坐在桌子上？那先把你擠出汁再端上來吧。\n");        

        if ( !arg || (arg != "chair" && arg != "yizi") )
                return notify_fail("你要坐在地板上？有個性！可惜的是這會影響歸雲莊的形象。\n");        
        
        if( query_temp("marks/sit", me) )
                return notify_fail("你已經坐在座位上了。\n");        
                        
        message_vision("$N找了個空位座下，等着上茶。\n", me);        
        if( query_temp("marks/tea_served", me)){
                message_vision("丫鬟走過來對$N説：喝飽了的就出去吧，別佔着地方！\n", me);
                message_vision("$N發覺眾人的眼光都在盯着自己，忙站起身來，尷尬地説：我只是試試這椅子結實不結實。\n", me);
                return notify_fail("");
        }
        set_temp("marks/sit", 1, me);

        call_out("serve_tea", 1, me);
        return 1;
}

int do_stand()
{
        object me = this_player();

        if( !query_temp("marks/sit", me) )
                return notify_fail("你已經站着了，是不是站久了有點發昏啊？\n");        
                        
        message_vision("$N拍拍屁股，站了起來。\n", me);        
        delete_temp("marks/sit", me);
        return 1;
}

int valid_leave(object me, string dir)
{
        if( query_temp("marks/sit", me) )
                return notify_fail("你打算連椅子也搬出去？\n");        

        if (dir == "east" && present("moli huacha", me))
//        if (random(3)) 
                return notify_fail("丫鬟跑過來説：沒喝完的也別帶走啊，考慮一下別人嘛。\n");
        
        return ::valid_leave(me, dir);
}