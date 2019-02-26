#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","城西客棧");
  set ("long", @LONG
這裏是家小客店。這幾天來住店的人很多，不知道還沒有空房子。
店小二正在門前熱情地招呼着客人。客店的門前掛着個大牌子，上面寫
着「住宿五兩紋銀」。門口掛着兩個大紅燈籠，上面寫着「平安」二字。
LONG);

  set("exits", ([ 
  
          "north":__DIR__"xijie2",
          "enter":__DIR__"shuifang",
         ]));
  set("objects",([
          __DIR__"npc/xiaoer2":1,
          ]));

  
  set("valid_startroom", 1);
  setup();
 
}

int valid_leave(object me,string dir)
{
        if( !query_temp("gived_money", me) && dir == "enter" )
                if(objectp(present("xiao",environment(me))))
                        return notify_fail("店小二攔住了你：客官，您還沒給錢呢!\n");
                else return notify_fail("掌櫃從裏面喊道：客官，給錢再住店啊!\n");
                return ::valid_leave(me,dir);
                return 1;
}