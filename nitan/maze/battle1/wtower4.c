// This program is a part of NT MudLIB

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short","石階");

        set("long",@LONG
這後山石階蜿蜒於戰場中，也不知通往何處。只見濃廕庇天，越
走越是陰森，不時還有野獸吼聲傳來，令人心中發毛。
LONG);

        set("exits",([
                "up" : __DIR__"wtower5",
                "down" : __DIR__"wtower3",
        ]));
        set("outdoors", "battle");

        set("objects", ([
                __DIR__"npc/guarder" : 1,
        ]));
        
        setup();
}

void init()
{
        string team_name;
        object ob;
        
        team_name = query("team_name", get_object(__DIR__"wtang"));
        ob = present("guarder", this_object());
        if( objectp(ob) && !query_temp("battle/team_name", ob) )
                set_temp("battle/team_name", team_name, ob);
}

int valid_leave(object me, string dir)
{
        mapping myfam;
        object ob, wp, *inv;
        int i, j=0;

        if( dir == "up" )
        {
                if( objectp(ob = present("guarder", this_object())) )
                {
                        if( query_temp("battle/team_name", me) != query_temp("battle/team_name", ob) )
                        {
                                if( objectp(wp=query_temp("weapon", ob)) )
                                        message_vision("$N對$n喝道：爾等邪魔歪道人物，要想過此路，得先問問我手中的"
                                                +query("name", wp)+"答應不答應！\n",ob,me);
                                else
                                        message_vision("$N對$n喝道：只要我在，爾等邪魔歪道人物，便休想過此路！\n", ob, me);
                                return notify_fail("\n");
                        }
                }
        }

        return ::valid_leave(me, dir);
}
