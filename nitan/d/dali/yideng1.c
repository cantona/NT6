//Cracked by Kafei
// yideng quest room 1
// acep

inherit ROOM;

void create()
{
        set("short", "無名山");
        set("long", @LONG
此處正是山嶺的頂部，山峯穿雲插天，山石滑溜，空山寂寂，只
見一道白龍似的大瀑布(waterfall)從對面雙峯之間奔騰而下，聲勢甚
是驚人，水聲在山谷間激盪迴響，轟轟洶洶，從嶺上望下去，瀑布旁
有一間草屋。
LONG );

        set("exits", ([
                "out" : __DIR__"maze1",
                ]));

        set("objects", ([ 
                CLASS_D("dali") + "/fisher" : 1,
        ]));

        set("item_desc", ([
                "waterfall" : "
你目光隨着瀑布向下流動，突然眼前金光閃爍，水底有物遊動，
定睛望去，只見一對金娃娃鑽在山石之中，兩條尾巴卻在外亂晃。",
                ]) );

        set("invalid_startroom", 1);
        set("outdoor","dalic");
        set("no_magic", 1);
        set("cost", 1);
        set("coor/x", -38000);
        set("coor/y", -80000);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_dive", "dive");
}

int do_dive(string arg)
{
        object me = this_player();

        if ( !arg || arg != "waterfall" )
                return notify_fail( "什麼？\n");

        message_vision("$N縱身跳入了瀑布中。\n", me);
        if ( me->query_skill("dodge",1) <= 50 ) {
                message_vision("$N雙足一入水，瀑布的急流便衝得他左搖右晃，難以站穩。一會兒便發出\n", me);
                message_vision("一聲慘嚎，被山洪衝得無影無蹤了。\n", me);
                set_temp("die_reason", "被山洪淹死了", me);
                me->receive_wound("qi",query("max_qi", me)+100);
        }

        if ( me->query_skill("dodge",1) > 50 && 
                me->query_skill("dodge",1) < 120 ) {
                message_vision("$N雙足一入水，瀑布的急流便衝得左搖右晃，難以站穩。只好勉力提氣\n", me);
                message_vision("，回身跳向岸邊。\n", me);
                me->unconcious();
        }

        if ( me->query_skill("dodge",1) >= 120 ) {
                me->move(__DIR__"yideng2");
                message("vision", me->name()+"“噗咚”的一聲跳了下來。\n",environment(me), ({me}) );
        }
        return 1;
} 
