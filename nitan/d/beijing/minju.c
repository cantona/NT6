// Updated by rama

inherit ROOM;
#include <ansi.h>

int do_open(string arg);
int do_knock(string arg);

void create() {
        set("short", "民居");
        set("long", @LONG
這裏是一件普普通通的民居，全屋只有屋角擺着一張牀(chuang)，
其它的什麼也沒有。
LONG );
        set("outdoors", "beijing");
        set("no_clean_up", 0);
        set("exits", ([
                "east" : "/d/beijing/shi_1",
        ]));
        set("item_desc", ([
                "chuang" : "木板作成的小牀，但是沒有一絲塵埃。\n" ,
        ]));

	set("coor/x", -2840);
	set("coor/y", 7710);
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
        if(arg=="chuang")
        return notify_fail("你用力拉了拉牀板，結果一點動靜都沒有！\n");
        else return 0;
}

int do_knock(string arg)
{
        object me;
        me = this_player();
        if (!arg||arg=="") 
                return notify_fail("你要敲什麼？\n");
          if (arg != "chuang")
                return notify_fail("你要敲什麼？\n");
          if( arg=="chuang" ) {
                message_vision("$N試著敲了敲牀板。\n", me);
                if( query("bunch/bunch_name", me) == "修羅門" )
                {
                        message_vision(HIB"牀板吱呀一聲開了，從裏面探出個頭來，看了$N兩眼説道：“原來是自家兄弟啊！”，
説完一把把$N拉了進去。\n"NOR, me);
                        me->move("/d/beijing/xlm_bjfb");
                        return 1;
                }
                if( query("bunch/bunch_name", me) != "修羅門" && query("shen", me) <= 0 )
                {
                        message_vision(HIB"牀板吱呀一聲開了，從裏面探出個頭來，看了$N兩眼説道：“是來投靠咱們修羅門的吧！”，
説完一把把$N拉了進去。\n"NOR, me);
                        me->move("/d/beijing/xlm_bjfb");
                        return 1;
                }
                if( good_bunch(me) || query("shen", me)>0 )
                { 
                        message_vision("牀板吱呀一聲開了，從裏面探出個頭來，看了$N兩眼説道：“你這種人也敢來此，活的不耐煩了麼？”\n門被重重的關上了。\n",me);  
                        return 1; 
                } 
                message_vision("門板吱呀一聲開了，從裏面探出個頭來，看了$N兩眼説道：“既然是本門的兄弟，就進來吧！”，
説完一把把$N拉了進去。\n",me);
                me->move("/d/beijing/xlm_bjfb"); 
                return 1; 
        }
        
        return 1;
}
  