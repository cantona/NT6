// /d/shenlong/qianlong 潛龍堂
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "潛龍堂");
        set("long", @LONG
這是神龍教的潛龍堂，居中兩張大竹椅，下面設了五張板凳，教主
和五龍使常在此商量密事，這兒非教主允許是不可以進入此地的。
LONG
        );
        set("exits", ([
                "out" : __DIR__"zhulin1",
        ]));
        set("objects", ([
                CLASS_D("shenlong")+"/hong" : 1,
                CLASS_D("shenlong")+"/su" : 1,
        ]));
        setup();
}

/*
void init()
{
        object *inv, me = this_player();

        if( !(query("family/family_name", me) == "神龍教" || 
                query("sg/spy", me)) )
        {
                inv = all_inventory(this_object());
                for(int i = 0; i < sizeof(inv); i++ )
                        if( (query("family/family_name", inv[i]) == "神龍教" || 
                                query("sg/spy", inv[i])) && living(inv[i]) )
                                inv[i]->kill_ob(me);
                me->start_busy(1);
        }
}
*/
