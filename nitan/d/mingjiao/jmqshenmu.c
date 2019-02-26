//JMQJIGUAN.C

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "巨木旗神木");
        set("long", @LONG
你眼前只見一棵大樹，高有百丈，十人也環抱不住。巨樹倚絕壁
而生，枝葉繁茂，藤蘿環繞，竟然無法一覽全貌。樹身有一處光滑無
比，是常有人摩挲而成。
LONG );
        set("exits", ([
                "east" : __DIR__"jmqshulin6",
        ])); 
        set("outdoors", "mingjiao");
        setup();
}

void init()
{
        add_action("do_climb", "climb");
}

int do_climb()
{
        object me=this_player();
        mapping mypar=query("party", me);
        me->receive_damage("qi",15);
        me->receive_wound("qi",15);
        
        message_vision(HIC "$N" HIC "三下兩下就順樹身爬了上去...\n" NOR, me);
        me->move(__DIR__"jmqdating");
        tell_object(me, HIC"你爬到了巨木旗大廳。\n"NOR);
        message("vision",HIC"只見"+query("name", me)+
                "順樹身爬了上來，靠在牆邊直喘氣！\n"NOR,
                environment(me), me);
        return 1;
}
