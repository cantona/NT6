#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW "【天外天】" NOR);
        set("long", HIW @LONG

                天         外         天

    這裏已是天界的盡頭，四周一片天際，茫茫無邊。遠方不時的有
一兩道光芒劃過，襯托着原本蒼白的天際。俯瞰而去，白雲茫茫，雲
氣正在向四處蔓延，似乎永無止盡。偶爾有陣陣梵音飄蕩而出，卻又
使這裏充滿着生氣。不遠處站着一位老者和一位年親人，似乎正注視
着你。

LONG NOR );

        set("sleep_room", 1);
        set("no_fight", 1);
        set("objects", ([
                __DIR__"npc/tongtian": 1,
                __DIR__"npc/tianshen": 1,
        ]));

        set("exits", ([
                "out" : "/d/city/wumiao",
        ]));
        set("sky", 1);
        setup();
}

void init()
{
        object me = this_player();
        
        if (! me->query("sky12/tianmen") && userp(me))
        {
                tell_object(me, HIG "通天老仙對你説道：你沒有使用過東皇鍾，是怎麼到天界來的，哼！\n" NOR);

                me->delete("sky12");
                me->save();
                me->move("/d/city/wumiao");
                
                //destruct(me);                
        }
        return ;        
}
