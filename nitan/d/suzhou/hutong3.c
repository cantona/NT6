// Room: /d/suzhou/hutong3.c
// Date: May 31, 98  Java
// Updated by rama
inherit ROOM;
#include <ansi.h>

int do_open(string arg);
int do_knock(string arg);

void create() {
        set("short", "衚衕");
        set("long", @LONG
這是一條黑暗、骯髒的小巷，空氣中彷彿飄揚着一股罪惡的氣息，
幾個流氓在遊蕩，向東南就能回到大街，你還是趕快走吧。旁邊有個
木門（door）。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "west"      : __DIR__"hutong2",
                "southeast" : __DIR__"dongdajie2",
        ]));
        set("item_desc", ([
                "door" : "厚厚的木門緊關着，有些年歲了。\n" ,
        ]));

        set("objects", ([
                "/d/city/npc/liumang" : 2,
        ]));
	set("coor/x", 1140);
	set("coor/y", -1040);
	set("coor/z", 0);
	setup();
}
void init()
{
        add_action("do_knock", "knock");
        add_action("do_open","open");
}
int do_open(string arg)
{
        if(arg=="door")
        return notify_fail("你用力拉了拉木門，結果一點動靜都沒有，看來是被反鎖了！\n");
        else return 0;
}

int do_knock(string arg)
{
        object me;
        me = this_player();
        if (!arg||arg=="")
                return notify_fail("你要敲什麼？\n");
          if (arg != "door")
                return notify_fail("你要敲什麼？\n");
          if( arg=="door" ) {
                message_vision("$N試著敲了敲木門。\n", me);
                if( query("bunch/bunch_name", me) == "修羅門" )
                {
                        message_vision(HIB"木門吱呀一聲開了，從裏面探出個頭來，看了$N兩眼説道：“原來是自己兄弟！”，
説完一把把$N拉了進去。\n"NOR, me);
                        me->move("/d/suzhou/xlm_zb");
                        return 1;
                }

                if( query("bunch/bunch_name", me) != "修羅門" && query("shen", me) <= 0 )
                {
                        message_vision(HIB"木門吱呀一聲開了，從裏面探出個頭來，看了$N兩眼説道：“是來投靠咱們修羅門的吧！”，
説完一把把$N拉了進去。\n"NOR, me);
                        me->move("/d/suzhou/xlm_zb");
                        return 1;
                }
                if( good_bunch(me) || query("shen", me)>0 )
                {
                          message_vision("木門吱呀一聲開了，從裏面探出個頭來，看了$N兩眼説道：“你這種人也敢來此，活的不耐煩了麼？”\n門被重重的關上了。\n",me);
                        return 1;
                }
                message_vision("木門吱呀一聲開了，從裏面探出個頭來，看了$N兩眼説道：“既然是本門的兄弟，就進來吧！”，
説完一把把$N拉了進去。\n",me);
                me->move("/d/suzhou/xlm_zb");
                return 1;
        }

        return 1;
}