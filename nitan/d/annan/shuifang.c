#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","睡房");
  set ("long", @LONG
這裡就是客棧的臥室了。只件這裡已經橫七豎八的躺了幾個人。你
來到這裡，不禁感到困了，打了一個呵欠。
LONG);

  set("exits", ([ 
  
        
          "out":__DIR__"kezhan",
         ]));
  set("sleep_room",1);
  set("valid_startroom", 1);
  setup();
 
}

int valid_leave(object me,string dir)
{
        if(dir=="out")
                delete_temp("gived_money", me);
        return ::valid_leave(me,dir);
}
