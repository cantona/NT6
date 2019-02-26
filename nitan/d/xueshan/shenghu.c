#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "聖湖");
        set("long", @LONG
眼前就是著名的聖湖，碧藍的湖面倒影着藍天和白雲，浩淼的水
面讓人心曠神怡。金碧輝煌的雪山寺清晰可見，再遠處是幾座延綿的
大雪山，其中最高大的是神山，相傳山中有神仙居住。雪山中融化的
雪水都匯入湖中。但是周圍卻是被極濃的霧氣所籠罩，使你的眼前一
片朦朧，瞧不清四周。
LONG );
        set("resource/water", 1);
        set("exits", ([
                "east" :  __FILE__,
                "west" :  __FILE__,
                "south" : __FILE__,
                "north" : __FILE__,
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "xuedao");

        setup();
}

int valid_leave(object me, string dir)
{
        int total_steps;

        if (! userp(me)
            || query("family/family_name", me) == "雪山寺"
            || query("family/family_name", me) == "血刀門" )
        {
                total_steps = 1; 
        } else
        {
                me->receive_damage("jing", 5);
                me->receive_wound("jing", 5);
                message_vision(HIM "\n突然間$N" HIM "發現眼前的景象有"
                               "些迷亂，不禁覺得頭暈目眩。\n\n" NOR, me);

                total_steps = 5;
        }

        if (dir == "east")
                addn_temp("taohua/steps", 1, me);

        if (dir == "south")
                addn_temp("taohua/steps", -1, me);

        if( query_temp("taohua/steps", me) == total_steps )
        {
                me->move(__DIR__"hubian1");
                delete_temp("taohua/steps", me);
                write(HIC "\n霧氣散開，你的眼前豁然開朗起來。\n\n" NOR);
                return -1;
        }  

        if( query_temp("taohua/steps", me) == -total_steps )
        {  
                me->move(__DIR__"tulu3");
                delete_temp("taohua/steps", me);
                write(HIC "\n霧氣散開，你的眼前豁然開朗起來。\n\n" NOR);
                return -1;
        }

        return ::valid_leave(me, dir);
}