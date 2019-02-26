inherit ROOM; 
#include <ansi.h> 
void leave_here(object me);

void create ()
{
  set ("short", "青木林");
  set ("long", HIG @LONG
四面都是幽暗的樹林，鳥語花香充溢其間，實在是絕美的風景。
然而，沒有什麼可以指示離開的去向，也沒有什麼能暗示出口在哪
裏。
LONG);

  set("exits", ([
        "east"      : __DIR__"spirit3",
        "west"      : __DIR__"spirit3",
        "south"     : __DIR__"spirit3",
        "north"     : __DIR__"spirit3",
        "northwest" : __DIR__"spirit3",
        "southwest" : __DIR__"spirit3",
      ]));
//  set("valid_startroom",1);
  set("no_magic", 1);
        setup();
}

/*
void init()
{
  add_action("do_quit", "quit");
}

int do_quit ()
{
  object me;
  me = this_player();

  set("startroom", base_name(environment(me)), me);
  tell_object(me,"暫時離開青木陣……\n");
  return 0; // return 0 to invoke normal quit
}
*/

int valid_leave (object me, string dir)
{
  object cao;
  int i;

  // me->set("startroom",base_name(environment(me)));
  if( i=query_temp("out_of_greenyard", me) )
  {
    i++;
    set_temp("out_of_greenyard", i, me);
    if (i > 5)
    {
      set_temp("lost_in_greenyard", 0, me);
      set_temp("out_of_greenyard", 0, me);
      
      call_out("leave_here",1,me);

      return 1;
    }
  }
  else if( !query_temp("lost_in_greenyard", me) )
  {
    set_temp("lost_in_greenyard", 1, me);
    call_out("found_outlet",240+random(240),me);
  }
  return 1;
}

// mon move this out of the valid_leave function
// to prevent an Illegal move error.
// 4/11/98
void leave_here(object me)
{
      object cao;

      me->move(__DIR__"outlet");
      if (! present("icedew",environment(me)))
      {
        cao = new("/quest/tulong/obj/xiaocao");
        cao->move(environment(me));
      }
      tell_object(me,HIG"綠草地上有一朵花！\n"NOR);
}

void found_outlet(object me)
{
  if(!me) return;
  set_temp("lost_in_greenyard", 0, me);
  set_temp("out_of_greenyard", 1, me);
}
