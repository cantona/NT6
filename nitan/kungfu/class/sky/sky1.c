#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW "【一重天】" NOR);
        set("long", HIW @LONG

                一         重         天

    這裏一片天際，茫茫雲海，四周不見任何事物。遠方一重雲彩從
地面升起，架起了一座雲梯(yunti)，似乎連接上層的天際…………


LONG NOR );

        set("exits", ([
                "out" : __DIR__"tianmen",
]));
        set("item_desc", ([
                "yunti" : HIW "\n一蓬白色的雲彩拔地而起，連接上層的天際。\n" NOR,
]));
        set("sleep_room", 1);
        set("objects", ([
                __DIR__"npc/tie": 1,
        ]));
        set("sky", 1);
        setup();
}

void init()
{
        object me = this_player();
        
        if (! me->query("sky12/tianmen") && userp(me))
        {
                tell_object(me, HIG "鐵傳甲對你説道：你沒有使用過東皇鍾，是怎麼到天界來的，哼！\n" NOR);

                me->delete("sky12");
                me->save();
                me->move("/d/city/wumiao");
                
                //destruct(me);                
        }
        
        add_action("do_move", "jump");
        add_action("do_move", "move");
        add_action("do_move", "tiao");
        add_action("do_move", "enter");
        add_action("do_move", "up");
}

int do_move(string arg)
{
        object paper,
        me = this_player();

        if (! arg || arg == "")
                return 0;

        if (arg == "yunti")
        {
                if ( objectp(present("tie chuanjia", environment(me)))
                     && me->query("sky12/floor") < 2)
                {
                        write(CYN "只聽鐵傳甲一聲暴喝：“這位" +
                              RANK_D->query_respect(me) + CYN
                              "，請停步。”\n" NOR);
                        return 1;
                }
                message_vision(HIW "\n$N" HIW "順着雲梯輕輕一"
                               "縱，身體便隨着氣流飄了上去……\n"
                               NOR, this_player());
                me->move("/kungfu/class/sky/sky2"); 
                return 1;
        }
        return 0;
}

