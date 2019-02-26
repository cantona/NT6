//entrance of gaochang.
//bye yuan
#include <ansi.h>

inherit ROOM;
   

void create ()
{
  set ("short", "高昌大門");
  set ("long", @LONG
    轉過了一排樹木，只見一座石山上嵌著兩扇鐵鑄的大門,
  大門看樣子重逾千鈞，據説是古代高昌國王為了抵禦強敵而設計的。
  門上鐵鏽斑駁，顯是歷時已久的舊物。但是門上的門環(huan)
  似乎可以扭(niu).門上寫着：
               ****************
               *              *
               *  高 昌 大 殿 *
               *              *
               ****************

LONG);

  set("outdoors", "gaochang");
  set("exits", ([ /* sizeof() == 2 */
  "southdown" : __DIR__"shijie3",
]));

  setup();
}

void init()
{
   add_action("do_niu", "niu");
}



void check_trigger()
{
   object room;
   object me=this_player();
   int exp,pot,score;
if( (int)query("left_trigger")==2

   &&   (int)query("right_trigger")==5
   &&   !query("exits/down") ) {
     message("vision", "鐵門忽然發出軋軋的聲音，露出一個向下的階梯。\n", this_object() );
      if( !(room = find_object(__DIR__"dadian")) )
              room = load_object(__DIR__"dadian");

     if( room = find_object(__DIR__"dadian") ) {
           set("exits/down", __DIR__"dadian");
           set("exits/up", __FILE__, room);
        
          message("vision", "鐵門忽然發出軋軋的聲音，露出一個向上的階梯。\n",room );
                if( !query("skybook/baima/damen", me) )
          {
                  set("skybook/baima/damen", 1, me);
                 exp=500+random(1000);
           pot=exp/2;
           score=pot/2;
           addn("combat_exp", exp, me);
           addn("potential", pot, me);
           tell_object(me,HIC"你成功打開了通往高昌大殿的鐵門！\n在這次歷練中你獲得了"+
                            chinese_number(exp)+"點經驗、"+
                     chinese_number(pot)+"點潛能以及"+
                     chinese_number(score)+"點江湖閲歷。\n\n"NOR);
          }
     }
     delete("left_trigger");
     delete("right_trigger");
     call_out("close_passage", 10);
   }
}

void close_passage()
{
   object room;

   if( !query("exits/down") ) return;
   message("vision", "鐵門忽然發出軋軋的聲音，將向下的通道蓋住了。\n",
     this_object() );
   if( room = find_object(__DIR__"dadian") ) {
     delete("exits/up", room);
     message("vision", "鐵門忽然發出軋軋的聲音，向上的通道又緩緩地被蓋住了。\n",
        room );
   }
   delete("exits/down");
   delete("left_trigger");
   delete("right_trigger");
}


int do_niu(string arg)
{
   string dir;
   object me=this_player();

   if( !arg || arg=="" ) return 0;

   if( arg=="huan" ) {
     write("你試着扭動門環，似乎可以左右滑動....\n");
delete("left_trigger");
delete("right_trigger");
     return 1;
   }
   if( sscanf(arg, "huan %s", dir)==1 ) {
     if( dir=="right" ) {
if(query("exits/down")) return notify_fail("鐵門已經被扭開了。\n");
        message_vision("$N將門環往右扭...，忽然「喀」一聲鐵門又移回原位。\n", me);
        addn("right_trigger", 1);
        check_trigger();
        return 1;
     } else if( dir=="left" ) {
if(query("exits/down")) return notify_fail("鐵門已經被扭開了。\n");
        message_vision("$N將門環往左扭...，忽然「喀」一聲鐵門又移回原位。\n", me);
        addn("left_trigger", 1);
        check_trigger();
        return 1;
     } else {
        write("你要將門環往哪邊扭？\n");
        return 1;
     }
   }
}


void reset()
{
   ::reset();
   delete("left_trigger");
   delete("right_trigger");
}
int valid_leave(object me, string dir)
{
 if(dir=="d" || dir=="down")
{
if( query("combat_exp", this_player())<100000 )
{
  return notify_fail("一股恐怖的氛圍從腳底心升起，使你兩腿顫抖不止，無法舉步。\n");
}

}
return ::valid_leave(me,dir);
}