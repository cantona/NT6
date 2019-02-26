// This program is a part of NITAN MudLIB

#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "高處不勝寒的工作室");
        set("long", @LONG
這是沒有建造工作室的巫師的臨時住處，這裏的設備非常簡單，只有
一些常用物品。
LONG );

        set("exits", ([ /* sizeof() == 1 */
                "north" : "/d/wizard/wizard_room",
                "down" : "/d/city/wumiao",
        ]));

        set("objects", ([
                //"/u/lonely/fuxinglaoren" : 1,
        ]));

        set("outdoors", "wizard");
        set("valid_startroom", 1);
        set("no_clean_up", 0);
        set("coor/x", 100000);
	set("coor/y", 100000);
	set("coor/z", 100000);
	setup();
        call_other("/clone/board/lonely_b", "???");
}

int valid_leave(object me, string dir)
{
        if (dir == "north" && ! wizardp(me))
                return notify_fail("那裏只有巫師才能進去。\n");

        return ::valid_leave(me, dir);
}

/*
void init()
{
        add_action("do_action", "");
        add_action("do_here", "come");
}

int do_action(string arg)
{
        object me,*ob,ob1;
        int i;
        me = this_player();
        ob = all_inventory(environment(me));
        
        if (this_player()->query("id") != "lonely")
        {
                string action = query_verb();

                switch (action) 
                {
                        case "smash"  :
                                write(HIW "這裏是高處不勝寒的房間，請不要惹高處不勝寒不快。\n" NOR);
                        return 1;
                }
        }
        if (arg != "") 
        {
                for (i = 0; i < sizeof(ob); i++)
                {
                        ob1 = query_snoop(ob[i]);
                        if (! living(ob[i])) continue;
                        if (objectp(ob1) && ob1->query("id") != "lonely")
                        {
                                snoop(ob1);
                                if (ob[i]->query("id") == "lonely")
                                tell_object(ob[i], HIW + ob1->name(1) + "對你的竊聽被中止。\n" NOR);
                        }
                }
        }
        return 0;
}

int do_here(string arg)
{
        object me, *user;
        
        user = users();
        me   = this_player();
        
        if (me->query("id") != "lonely" || arg != "here")
                return notify_fail("What are you doing ?");
        
        foreach (object player in user)
        {
                if (wizardp(player))
                        player->move("/u/lonely/workroom.c");
                
        }
        return 1;       
}

*/
