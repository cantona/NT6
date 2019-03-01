// pine_forest10.c 鬆林小溪
// Last Modified by winder on Aug. 18 2002

#include <localtime.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        mixed *local;
        object *ob;
        local = localtime(time()*60);

        set("short", HIM"鬆中草地"NOR);
        set("long", @LONG
眼前霍豁然開朗，密林中露出一片空地，中間一條溪水潺潺流過。
溪邊奇花異草，長得特別鮮艷。
LONG
        );
        if( local[LT_MON] > 5 && local[LT_MON] < 10 )
                set("objects", ([
                        VEGETABLE_DIR"heshouwu" : 1,
                        __DIR__"npc/python" : 1
                ]));
        else
                set("objects", ([
                        __DIR__"npc/python" : 1
                ]));
        set("exits", ([
                "east" : __DIR__"pine_forest"+(random(2)),
                "west" : __DIR__"pine_forest"+(random(2)),
        ]));
        set("outdoors", "wudang");
        setup();
}

void init()
{
        object me = this_player();
        
        if( !objectp(query_temp("armor/boots", me)) )
                me->receive_damage("qi", 10, "被鬆針紮死了");  

}
