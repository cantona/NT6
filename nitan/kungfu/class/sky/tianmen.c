#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW "【通天門】" NOR);
        set("long", HIW @LONG
你來到這裏，發現這裏茫茫一片雲海。眼前一座宏偉的敞開的大
門，大門的柱子旁依偎着一位男子，似乎對你的到來毫不在意。
LONG NOR );
        set("exits", ([
                "enter" : __DIR__"sky1",
]));
        set("sleep_room", 1);
        set("objects", ([
                __DIR__"npc/li": 1,
        ]));

        setup();
}

int valid_leave(object me, string dir)
{
        object ob;

        if ( dir == "enter" && objectp(present("li xunhuan", environment(me)))
             && me->query("sky12/floor") < 1)
        {
                write(HIG "李尋歡説道：要進入天界得先過我這關！\n" NOR);
                return notify_fail("李尋歡擋住了你的去路。\n");
        }

        tell_object(me,  HIW "\n你進入了十二重天之第一重天……\n" NOR);

        CHANNEL_D->do_channel(this_object(), "rumor", HIM "聽説" + me->name() + HIM + "闖入天界第一重天。\n\n" NOR);

        return ::valid_leave(me, dir);
}
void init()
{
        object me = this_player();
        
        if (! me->query("sky12/tianmen") && userp(me))
        {
                tell_object(me, HIG "李尋歡對你説道：你沒有使用過東皇鍾，是怎麼到天界來的，哼！\n" NOR);

                me->delete("sky12");
                me->save();
                me->move("/d/city/wumiao");
                
                //destruct(me);                
        }
        return ;        
}
