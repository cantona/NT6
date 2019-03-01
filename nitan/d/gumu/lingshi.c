// Room: /d/gumu/lingshi.c
// Last Modifyed by Winder on Jan. 14 2002

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", HIC"靈室"NOR);
        set("long", @LONG
只見空空曠曠的一座大廳上並列放著五具石棺。凝神細看，見兩具
石棺棺蓋已密密蓋著，原來是古墓派祖師林朝英和小龍女師傅的安身之
處。另外二具的棺蓋(guangai)卻只推上一半，也不知其中有無屍體。
LONG        );

        set("exits", ([ 
                "out" : __DIR__"shishi5",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3000);
        set("coor/y", -40);
        set("coor/z", 80);
        setup();
}

void init()
{
        add_action("do_tui", "tui");      
        add_action("do_tang","tang");
}

int do_tui(string arg)
{
        object me=this_player();

        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙著哪！\n");
        if ( arg =="guangai")
        {
                message_vision(YEL"$N使勁推開了棺蓋。\n"NOR,me);
                set_temp("marks/石棺", 1, me);
                return 1;
        }
        return notify_fail("你要推什麼？\n");
}

int do_tang(string arg)
{
        object me=this_player();       

        if( !query_temp("marks/石棺", me))return 0;
        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙著哪！\n");
        if ( arg =="guan")
        {
                delete_temp("marks/石棺", me);
                me->move(__DIR__"shiguan");
                message_vision(HIY"$N躺進了石棺，棺內已無轉側餘地。\n"NOR,me);
                return 1;
        }
        return notify_fail("你想躺在哪裡？\n");
}