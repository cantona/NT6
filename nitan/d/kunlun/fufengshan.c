// Room: /d/kunlun/fufengshan.c
// Last Modified by winder on Nov. 14 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

int do_climb();

void create()
{
        set("short", "扶峰山");
        set("long", @LONG
扶峰山極高且十分陡峭，山腰以上盡沒入茫茫雲海中，峰頂終年積
雪，山腰以下卻是鬱鬱蒼蒼，林木茂密，花團錦簇，春意爛漫。
LONG );
        set("outdoors", "kunlun");
        set("exits", ([
                "northeast" : __DIR__"bainiuling",
                "enter" : __DIR__"houyuan", 
        ]));
/*        set("objects",([
                "/kungfu/class/kunlun/gaozecheng.c" :   1,
                "/kungfu/class/kunlun/jiangtao.c" :   1,
        ]));
*/
        set("no_clean_up",0);
        create_door("enter", "小門", "out", DOOR_CLOSED);
        set("coor/x", -119980);
        set("coor/y", 40170);
        set("coor/z", 90);
        setup();
}

void init()
{
        add_action("do_climb", "climb");
}
int do_climb()
{
        object me= this_player();

        if( random((int)me->query_skill("dodge",1))<=30)
        {
                me->receive_damage("qi", 50);
                me->receive_wound("qi", 50);
                message_vision(HIR"$N一不小心腳下踏了個空... 啊...！\n"NOR, me);
                me->move(__DIR__"fufengshan.c");
                tell_object(me,
                HIR"你從山上滾了下來，只覺得渾身無處不疼，還受了幾處傷。\n"NOR);
                message("vision",HIR"只見"+query("name", me)+
                "從山上骨碌碌地滾了下來，躺在地上半天爬不起來！\n"NOR, environment(me), ({me}));
                return 1;
        }
        message("vision",
        me->name() + "提一口真氣，足尖連點數下，發足向山上奔去。\n",
                environment(me), ({me}) );
        me->move(__DIR__"sanshengao");
        return 1;
}