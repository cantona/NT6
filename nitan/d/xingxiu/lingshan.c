// lingshan.c
// Modified by Dumbness, 2003-5-24 0:57

#include <localtime.h>
#include <ansi.h>;
inherit ROOM;

void create()
{
        mixed *local;
        local = localtime(time());

        set("short", "靈山");
        set("long", @LONG
從天池起步，攀上高插雲霄、四時積雪的靈山。一到雪線附近，
一股秋菊似的幽香突然襲來，原來朵朵鮮花挺立在這寒風中，給冰雪
世界增添了春色，這就是被叫作 "高山玫瑰" 的雪蓮。雪蓮單單生長
在這氣候嚴寒、土質貧瘠的冰山雪嶺上，每年盛夏開花，一直開到深
秋，不畏冰雪，即使在雪花紛飛中，依然吐苞放瓣，敢於同雪花爭艷，
最終與莖同枯而不落。
LONG );
        set("exits", ([
                "down" : "/d/xingxiu/tianchi",
        ]));
        
        if( ( local[LT_MON] >= 4 && local[LT_MON] <= 9 ) && (random(5) == 1) ) 
        {
        
                set("objects", ([
                        DRUG_D("xuelian") : 1,
                ]));
        }

        set("outdoors", "tianshan");
        setup();
}

int valid_leave(object me, string dir)
{
        object *inv;
        int i, flag, j=0;

        inv = all_inventory(me);

        for (i=0; i<sizeof(inv); i++)
                if( query("id", inv[i]) == "xuelian" )
                        j++;

        if( random((int)me->query_skill("dodge")) <= 30
                || ( j > 0 ) )
        {
                me->receive_damage("qi", 100);
                me->receive_wound("qi",  100);
                message_vision(HIR"$N一不小心腳下一滑，... 啊...！\n"NOR, me);
                me->move("/d/xingxiu/tianchi");
                tell_object(me, HIR"你從峰頂梭地一下滑了下來，只覺得渾身無處不疼，還受了幾處傷。\n"NOR);
                message("vision",HIR"只見"+query("name", me)+"梭地一下從峰頂上直滑下來，差點兒掉進天池。\n"NOR,environment(me),me);
                if ( j > 0 )
                        for (i=0; i < sizeof(inv); i++) 
                        {
                                if ( !userp(inv[i]) &&
                                        !inv[i]->query_autoload() && 
                                        !query("armor_prop/armor", inv[i]) )
                                {
                                        destruct(inv[i]);
                                        flag += 1;
                                }
                        }
                if ( flag ) tell_object(me, "你身上的東西都撲通撲通掉進了天池。\n");
        }
        return ::valid_leave(me, dir);
}

