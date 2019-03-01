#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "柴房");
        set("long", @LONG
這是一間矮小的瓦房，平時作為堆放雜物所用。房屋裡布
滿了蛛網，地面滿是灰塵。看樣子已經很久沒有人打掃了。柴
房的一角斜放著幾捆幹柴。
LONG);
        set("exits", ([
                "west" : __DIR__"ma_dayuan",
        ]));
        set("region", "yangzhou");
        set("no_clean_up", 0);
        set("objects", ([
                "/d/wudu/obj/ganchai" : 2,
        ]));
	set("coor/x", 40);
	set("coor/y", -20);
	set("coor/z", 0);
	setup();
}

void init()
{
        object me = this_player();

        if( query("family/family_name", me) == "五毒教" )
        {
                tell_object(me, HIR "\n你突然發現一只色彩斑斕的蜘蛛，竟"
                                "似五毒教的獨門密信。\n" NOR);
                set_temp("want_back_wudu", 1, me);

                remove_call_out("letter");
                call_out("letter", 3, me);
        }
        add_action("do_back", "back");
}

void letter(object me)
{
        if (environment(me) != this_object())
                return;

        if( !query_temp("want_back_wudu", me) )
                return;

        tell_object(me, WHT "  □□□□□□□□\n"
                            "  □柴房水缸下有□\n"
                            "  □本教密道能夠□\n"
                            "  □直通(" HIY "back" NOR + WHT ")五□\n"
                            "  □毒教  齊雲傲□\n"
                            "  □□□□□□□□\n" NOR);
}

int do_back()
{
        object me = this_player();

        if( query_temp("want_back_wudu", me) )
        {
                message("vision", HIC "忽然間只見" + me->name() +
                                  HIC "身形一晃，竟沒了蹤影。\n" NOR,
                                  environment(me), ({me}));
                me->move("/d/wudu/midao5");
                tell_object(me, HIC "\n你鑽進了柴房水缸下的密道。\n\n" NOR);
        }
        return 1;
}