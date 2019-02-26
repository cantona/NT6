// Updated by rama

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "衚衕");
        set("long", @LONG
這裏是襄陽城內老百姓的居住區。只見衚衕兩邊是有些小店面，
有米行、小雜貨鋪等。一些居民從這裏進進出出。你似乎覺得這裏有
些詭祕。旁邊有個小木門（door）。
LONG );
        set("outdoors", "xiangyang");
        set("exits", ([
                "south" : __DIR__"jiekou1",
        ]));
        set("objects", ([
                __DIR__"npc/girl" : 2,
        ]));

        set("item_desc", ([
                "door" : "厚厚的木板門，看起來相當陳舊。\n" ,
        ]));

        set("coor/x", -7830);
	set("coor/y", -730);
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
        return notify_fail("你用力推了推門，結果一點動靜都沒有！看來是從裏面反鎖了。\n");
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
                if( query("bunch/bunch_name", me) != "黑白道" && query("shen", me) <= 0 )
                {
                        message_vision(HIB"木門吱呀一聲開了，從裏面探出個頭來，看了$N兩眼説道：“是來投靠咱們黑白道的吧！”，
説完一把把$N拉了進去。\n"NOR, me);
                        me->move(__DIR__"hbd_xyfb");
                        return 1;
                }
                if( good_bunch(me) || query("shen", me)>0 && query("bunch/bunch_name", me) != "黑白道" )
                { 
                        message_vision("木門吱呀一聲開了，從裏面探出個頭來，看了$N兩眼説道：“你這種人也敢來此，活的不耐煩了麼？”\n門被重重的關上了。\n",me);  
                        return 1; 
                } 
                message_vision("門板吱呀一聲開了，從裏面探出個頭來，看了$N兩眼説道：“既然是本幫的兄弟，就進來吧！”，
説完一把把$N拉了進去。\n",me);
                me->move(__DIR__"hbd_xyfb"); 
                return 1; 
        }
        
        return 1;
}
  