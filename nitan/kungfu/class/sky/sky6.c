#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW "【六重天】" NOR);
        set("long", HIW @LONG

                六         重         天

    這裏一片天際，茫茫雲海，四周不見任何事物。遠方一重雲彩從
地面升起，架起了一座雲梯(yunti)，似乎連接上層的天際…………

LONG NOR );
        set("item_desc", ([
                "yunti" : HIW "\n一蓬白色的雲彩拔地而起，連接上層的天際。\n" NOR,
]));
        set("sleep_room", 1);
        set("objects", ([
                __DIR__"npc/master/yideng"     :  1,
                __DIR__"npc/master/huang"      :  1,
                __DIR__"npc/master/ouyangfeng" :  1,
                __DIR__"npc/master/hong"       :  1,                
        ]));

        setup();
}

void init()
{
        add_action("do_move", "jump");
        add_action("do_move", "move");
        add_action("do_move", "tiao");
        add_action("do_move", "enter");
        add_action("do_move", "up");
}

int do_move(string arg)
{
        object me = this_player();

        if (! arg || arg == "")
                return 0;

        if (arg == "yunti")
        {
                if ( (objectp(present("huang yaoshi", environment(me)))
                  || objectp(present("hong qigong", environment(me)))
                  || objectp(present("ouyang feng", environment(me)))
                  || objectp(present("yideng dashi", environment(me))))
                    && me->query("sky12/floor") < 7)
                {
                        write(CYN "只見一個人影突然晃動，擋在你面前。\n" NOR);
                        return 1;
                }
                message_vision(HIW "\n$N" HIW "順着雲梯輕輕一"
                               "縱，身體便隨着氣流飄了上去……\n"
                               NOR, this_player());
                message_vision(HIW "\n$N" HIW "順着雲梯輕輕一"
                               "縱，身體便隨着氣流飄了上去……\n"
                               NOR, this_player());
                me->move("/kungfu/class/sky/sky7"); 
                return 1;
        }
        return 0;
}

