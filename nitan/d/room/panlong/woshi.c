// woshi.c 盤龍居卧室

#include <room.h>
#include <ansi.h>

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
        set("short", "卧室");
        set("long", @LONG
這是主人的卧室，收拾得井井有條。南窗下是一張大牀，牀邊有一個
櫃子。推開窗户可以看到下面的花園，還可嗅到陣陣花香，非常愜意。遠
處是一大片竹林。
LONG );

        set("default_long", "這是主人的卧室，收拾得井井有條。南窗下是" /* EXAMPLE */
                            "一張大牀，牀邊有一個櫃子。推開窗户可以看" /* EXAMPLE */
                            "到下面的花園，還可嗅到陣陣花香，非常愜意" /* EXAMPLE */
                            "。遠處是一大片竹林。");                   /* EXAMPLE */
                                                                       /* EXAMPLE */

        set("exits", ([
                "down" : __DIR__"jusuo",
        ]));

//**    set("objects", ([
//**            "/adm/npc/obj/xiang" : 1,
//**    ]));

//**    set("sleep_room", 1);
//**    set("loving_room", 1);
        set("no_fight", 1);
        setup();
//**
//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}

void init()
{
//**    add_action("do_findbaby", "xunzhao");
}

int do_findbaby(string arg)
{
        object me = this_player(), baby;
        string file;

//**    if (! arg || (arg != "baby" && arg != "child") ||
//**        ! is_room_owner(me)) 
                return 0;

        if( !query("couple/child_id", me) )
                return notify_fail("你又還沒有孩子，來這裏湊什麼熱鬧啊？\n");

        if( objectp(baby=find_living(query("couple/child_id", me)) )
        &&  environment(baby) && baby->is_baby())
                return notify_fail("你們的孩子已經跑出去玩了，好好四處找找吧！\n");

        if( query("gender", me) == "女性" )
                file=read_file("/data/baby/"+query("id", me)+".o");
        else file=read_file("/data/baby/"+query("couple/couple_id", me)+".o");

        if (stringp(file))
        {
                baby = new("/clone/user/baby");

                baby->load_baby(me);
                baby->move(environment(me));
                message_vision("你忽然看到牀底下" +
                        ({"探出一顆小腦瓜", "伸出一雙小腳丫", "伸出一支小手"})
                        [random(3)] + "．．．\n", me);

        } else
        {
                tell_object(me, MAG "你們的孩子不幸夭折了，請節哀吧。\n" NOR);
                delete("couple/child_id", me);
                delete("couple/child_name", me);
        }
        return 1;
}      
