// Room: /d/xiakedao/chashi.c

#include <ansi.h>
inherit ROOM;

void init();
int do_sit(string);

void delete_served(object);

void create()
{
        set("short", "茶室");
        set("long", @LONG
這是一個石洞，三枝紅燭照耀得全洞明亮。洞內坐滿了人，一
個童子忙前忙後，滿屋的果香和茶香，沁人心脾。屋裏四周得體地
擺着些桌子(table)和椅子(chair)。
LONG );
        set("no_fight", 1);
        set("exits", ([
                "east" : __DIR__"neiting",
        ]));
        set("item_desc", ([
            "table" : "一張精緻的木製小桌，上面放着一些茶具。\n",
            "chair" : "一隻青竹打製的靠椅，躺上去搖搖晃晃，好舒服耶！\n",
        ]));

        set("objects",([
                __DIR__"npc/tongzi" : 1,
                "/d/wudang/obj/mitao" : 4,
                "/d/wudang/obj/xiangcha" : 1,
        ]));
        set("coor/x", -3100);
        set("coor/y", -25000);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_sit", "sit");
}

int do_sit(string arg)
{

        if ( !arg || (arg != "chair") )
                return notify_fail("你要坐什麼上面？\n");

        if( query_temp("marks/sit", this_player()) )
                return notify_fail("你已經有了個座位了。\n");

        set_temp("marks/sit", 1, this_player());
        return notify_fail("你找了個空位座下，等着上茶。\n");
}

int valid_leave(object me, string dir)
{

        if (  (dir == "east")
           && ( present("xiang cha", this_player())
                || present("mi tao", this_player()) )
           && objectp(present("tongzi", environment(me))) )
        switch ( random(2) )
        {
        case 0:
         return notify_fail
                ("童子把嘴一撇：吃飽了喝足了還不夠，臨走懷裏還揣上一些！\n");
        case 1:
         message_vision("童子對$N鞠了個躬：島主吩咐，飲食不得帶出茶房。", me);
         return notify_fail("\n");
         break;
        }

        delete_temp("marks/sit", me);
        delete_temp("tea_cup", me);
        return ::valid_leave(me, dir);
}