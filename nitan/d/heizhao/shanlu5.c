// Room: /heizhao/shanlu5.c
// Date: Dec. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "泥沼");
        set("long", @LONG
“啊喲”一聲，你的雙足已陷入泥中，直沒至漆，你急忙提氣
後躍，硬生生把兩隻腳拔了出來，一股污泥的臭味極是刺鼻。向前
望去，眼前一團茫茫白霧裹着兩間茅屋 (house)，燈光便從茅屋中
射出。
LONG );
        set("outdoors", "heizhao");
        set("no_clean_up", 0);
        set("item_desc", ([
                "house" : "茅屋一方一圓，建在污泥湖沼之中，四周無處落腳。看來
你只好跳進去了。\n",
        ]));
        set("exits", ([
                "southeast"  : __DIR__"maze2",
        ]));
        set("coor/x", -5100);
        set("coor/y", -1500);
        set("coor/z", -5);
        setup();
}

void init()
{
        add_action("do_jump", "jump");
}

int do_jump(string arg)
{
        object me=this_player();

        if( me->is_busy() )
                return notify_fail("你上一個動作還沒有完成！\n");

        if( !arg || (arg != "left" && arg != "right"))
                return notify_fail("你要往左跳還是往右跳啊？\n");
        message_vision(HIY "$N勁發足跟，高高躍起，躍牆而過！\n"NOR,me);

        if (random(me->query_skill("dodge",1)) < 60)
        {
message_vision(HIR"結果只聽一聲悶哼，$N還沒躍到牆頭就掉在泥沼裏了...\n"NOR,me);
message_vision(HIB"屋裏伸出一隻女人的手，提起$N的衣領，一拋就拋出林外去了。\n"NOR,me);
                me->receive_damage("qi", 100);
                me->start_busy(random(50));
                me->move(__DIR__"shanlu1");
                return 1;
        }
        if (arg == "right")
        {
message_vision(HIC"只聽一聲轟響，真是帥呆了，$N正掉在水塘裏！\n"NOR,me);
message_vision(HIB"屋裏伸出一隻女人的手，提起$N的衣領，一拋就拋出林外去了。\n"NOR,me);
                me->receive_wound("qi", 200);
                me->receive_damage("qi", 200);
                me->start_busy(random(20));
                me->move(__DIR__"shanlu1");
                return 1;
        }
message_vision(HIY"$N越過高牆，落在院子左首實地上。\n"NOR,me);
        me->move(__DIR__"hzyuanzi");
        return 1;
}