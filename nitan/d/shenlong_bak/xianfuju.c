// /d/shenlong/xianfuju 東廂房(仙福居)
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
#include <room.h>
inherit ROOM;

void init()
{
        add_action("do_get", "get");
}

void create()
{
        set("short", "仙福居");
        set("long", @LONG
神龍教的仙福居，雖說是廂房，卻也十分寬敞，陳設雅潔，桌上架
上擺滿了金玉古玩，壁上懸著字畫，床上被褥華美，居然有點皇宮中的
派頭。你真想躺在床上美美地睡上它一覺。
LONG
        );
        set("sleep_room", 1);
        set("no_fight", 1);
        set("no_steal", 1);
        set("exits", ([
                "north" : __DIR__"shibanlu",
        ]));
        set("no_clean_up", 0);

        setup();
}

int do_get(string arg)
{
        object obj;

        if( arg && objectp(obj = present(arg, environment(this_player()))) &&
                obj->is_character() )
        {
                write("你不能搬動玩家的身體。\n");
                return 1;
        }
        else
                return 0;
}
/*
int valid_leave(object me, string dir)
{
        object room;

        if ( !::valid_leave(me, dir) )
                return 0;

        if(!(room = find_object(__FILE__)) )
                room = load_object(__FILE__);
        if(objectp(room))
        {
                addn_temp("person_inside", -1, room);
                if( room->addn_temp("person_inside",-1) <= 0 )
                        delete_temp("person_inside", room);
        }

        return 1;
}
*/
