#include <ansi.h>
inherit ROOM;

int do_knock(string arg);
int do_open(string arg);

void create()
{
        set("short", "郭莊");
        set("long", @LONG
莊園的大匾上是「郭莊」兩個大字。硃紅色的大門(gate)緊緊關
閉着，裏面靜悄悄的一點聲音都沒有。
LONG );
        set("exits", ([
                "east" : __DIR__"dadao1",
        ]));
        set("objects", ([
                "/clone/quarry/gou2" : 2,
        ]));
        set("item_desc", ([
                "gate" : "硃紅的大門緊閉着，敲敲(knock)看吧。\n"
        ]));
        set("no_clean_up", 0);
	set("coor/x", 770);
	set("coor/y", -2020);
	set("coor/z", 0);
	setup();
        // replace_program(ROOM);
}

void init()
{
        add_action("do_knock", "knock");
        add_action("do_open","open");
}
int do_open(string arg)
{
        if(arg=="gate")
        return notify_fail("你用力推了推門，結果一點動靜都沒有！看來是從裏面反鎖了。\n");
        else return 0;
}

int do_knock(string arg)
{
        object me;
        me = this_player();
        if (!arg||arg=="")
                return notify_fail("你要敲什麼？\n");
          if (arg != "gate")
                return notify_fail("你要敲什麼？\n");
          if( arg=="gate" ) {
                message_vision("$N試著敲了敲門。\n", me);
                if( query("bunch/bunch_name", me) != "小刀會" && query("shen", me) <= 0 )
                {
                        message_vision(HIB"大門吱呀一聲開了，從裏面探出個頭來，看了$N兩眼説道：“是來投靠咱們小刀會的吧！”，
説完一把把$N拉了進去。\n"NOR, me);
                        me->move("/d/hangzhou/xdh_hzfb");
                        return 1;
                }
                if( good_bunch(me) || query("shen", me)>0 )
                {
                        message_vision("大門吱呀一聲開了，從裏面探出個頭來，看了$N兩眼説道：“你這種人也敢來此，活的不耐煩了麼？”\n門被重重的關上了。\n",me);
                        return 1;
                }
                message_vision("大門吱呀一聲開了，從裏面探出個頭來，看了$N兩眼説道：“既然是本幫的兄弟，就進來吧！”，
説完一把把$N拉了進去。\n",me);
                me->move("/d/hangzhou/xdh_hzfb");
                return 1;
        }

        return 1;
}