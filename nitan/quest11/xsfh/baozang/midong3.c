// by tangfeng 8/2004

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "密洞");
        set("long", @LONG
洞內深窈無比，神祕難測。你一走進來，便發覺洞中叉洞多如迷宮，怪異
莫測，似乎黝黑無底。
LONG);
        set("exits", ([
                "east" : __FILE__,
                "south" : __FILE__,
                "west" : __FILE__,
                "north" : __FILE__,
        ]));
   set("quest", 1);
   set("baozang",1);
   setup();

}
void init()
{
   add_action("do_use", "use");
}
int do_use(string arg)
{
   object ob, me;
   me = this_player();
   if(!living(me) ) return 0;
   if (me->is_busy() || me->is_fighting())
      return notify_fail("你正忙着哪！\n");
   if(!objectp(ob = present("fire", me)))
      return notify_fail("你手中沒有火折。\n");
   if( !arg || arg=="" ) return 0;
   if( arg == "fire" ) {
      message_vision(BLU"$N點燃火折，把洞內照亮了一些，微弱的火光一閃一閃的。\n"NOR, me);
      message_vision(BLU"$N似乎看出密洞的一些門道。\n"NOR, me);
      me->set_temp("baozang/north_",2+random(8));//北
      me->set_temp("baozang/south_",2+random(8));//南
      me->set_temp("baozang/east_",2+random(8));//東
      me->set_temp("baozang/west_",2+random(8));//西
      tell_object(me,HIY"你又暗裏推算一番，原來如此：東行"+chinese_number(me->query_temp("baozang/east_"))+"步，西行"+chinese_number(me->query_temp("baozang/west_"))
                        +"，北折"+chinese_number(me->query_temp("baozang/north_"))+"，南迴"+chinese_number(me->query_temp("baozang/south_"))+"即可！\n"NOR);
      return 1; 
   }
}
int valid_leave(object me, string dir)
{
        if ( dir == "north")
              if(userp(me)) me->add_temp("baozang/north",1);
        if ( dir == "south")
              if(userp(me)) me->add_temp("baozang/south",1);         
        if ( dir == "east")
              if(userp(me)) me->add_temp("baozang/east",1);
        if ( dir == "west")
              if(userp(me)) me->add_temp("baozang/west",1);         

        if (me->query_temp("baozang/north") >= 13||me->query_temp("baozang/south") >= 13
           ||me->query_temp("baozang/east") >= 13||me->query_temp("baozang/west") >= 13)
        {
         	  message_vision(HIG"$N像沒頭蒼蠅一樣在洞裏瞎鑽，結果一頭撞在洞壁上。你覺得你暈乎乎的，似乎撞傻了。\n"NOR, me);
            me->delete_temp("baozang/north");
            me->delete_temp("baozang/south");
            me->delete_temp("baozang/east");
            me->delete_temp("baozang/west");
            me->start_busy(1);
            return notify_fail(HIB"你吃驚地發現，你現在的位置竟然就是最初的位置。\n"NOR);
        }  
        if (me->query_temp("baozang/north") == 10 && me->query_temp("baozang/south") == 10
          && me->query_temp("baozang/east") == 10 && me->query_temp("baozang/west") == 10)
        {
         	  message_vision(HIC"$N像沒頭蒼蠅一樣在洞裏瞎鑽，結果一頭撞在洞壁上。你覺得你暈乎乎的，似乎撞傻了。\n"NOR, me);
            me->delete_temp("baozang/north");
            me->delete_temp("baozang/south");
            me->delete_temp("baozang/east");
            me->delete_temp("baozang/west");
            me->delete_temp("baozang/north_");
            me->delete_temp("baozang/south_");
            me->delete_temp("baozang/east_");
            me->delete_temp("baozang/west_");
            me->move(__DIR__"bingqiku");
            tell_room(environment(me), me->name()+"從西邊的密洞走了過來。\n", ({ me }));
            return notify_fail(HIB"你吃驚地發現，你終於走出了密洞。\n"NOR);
        } 
        if (me->query_temp("baozang/north_") 
            && me->query_temp("baozang/north") == me->query_temp("baozang/north_") 
            && me->query_temp("baozang/south") == me->query_temp("baozang/south_") 
            && me->query_temp("baozang/east") == me->query_temp("baozang/east_") 
            && me->query_temp("baozang/west") == me->query_temp("baozang/west_") )
        {
            me->delete_temp("baozang/north");
            me->delete_temp("baozang/south");
            me->delete_temp("baozang/east");
            me->delete_temp("baozang/west");
            me->delete_temp("baozang/north_");
            me->delete_temp("baozang/south_");
            me->delete_temp("baozang/east_");
            me->delete_temp("baozang/west_");
            me->move(__DIR__"bingqiku");
            tell_room(environment(me), me->name()+"從西邊的密洞走了過來。\n", ({ me }));
            return notify_fail(HIY"你累得半死，終於走出了密洞。\n"NOR);
        }                          
        return ::valid_leave(me,dir);
}
 
