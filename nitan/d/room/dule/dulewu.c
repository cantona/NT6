// dulewu.c 獨樂居小屋
#include <ansi.h>

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
        set("short", "小屋");                   /* EXAMPLE */
//**    set("short", "ROOM_NAME小屋");
        set("long", @LONG
屋子不大，靠窗的地方擺了一張床，屋中一張桌，幾只椅，非常簡單。
恐怕只有甘于寂寞的人才住得了這種簡樸的屋子。
LONG );

        set("default_long", "屋子不大，靠窗的地方擺了一張床，"   /**/
                            "屋中一張桌，幾只椅，非常簡單。"     /**/
                            "看來主人是一個甘于平淡寂寞的人。"); /**/

//**    set("objects", ([
//**            "/adm/npc/obj/xiang" : 1,
//**    ]));
                                                                 /**/
        setup();

        set("exits", ([                         /* EXAMPLE */
                "south" : __DIR__"xiaoyuan",    /* EXAMPLE */
        ]));                                    /* EXAMPLE */
                                                /* EXAMPLE */
//**    set("KEY_DOOR", ([
//**            "exit" : "south",
//**            "room" : __DIR__"xiaoyuan",
//**    ]));
//**

//**    set("sleep_room", 1);
//**    set("loving_room", 1);
        set("no_fight", 1);
//**
//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}

void init()
{
//**    ::init();
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
                return notify_fail("你又還沒有孩子，來這裡湊什麼熱鬧啊？\n");

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
                message_vision("你忽然看到床底下" +
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