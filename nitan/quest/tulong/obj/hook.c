inherit ITEM;
#include <ansi.h>

void create()
{
        set_name("小鈎子", ({ "hook" , "gou zi"}) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", "一個小小的鈎子，看起來很象用來釣魚的鈎子，也許你可以用
它來做一個釣魚杆。(make) \n");
                set("value", 10);
        }
}

void init()
{
   if(this_player()==environment())
   add_action("do_make", "make");
}

int do_make(string arg)
{
   int i,xxan=0,taozhi1=0;
   object fpole, me, xan, taozhi, *inv;

   me = this_player();
   inv = all_inventory(me);
   for(i=0; i<sizeof(inv); i++)
   {
      if( query("name", inv[i]) == "細麻線"){xxan=1;xan=inv[i];}
      if( query("name", inv[i]) == "桃枝"){taozhi1=1;taozhi=inv[i];}
   }
   if ( xxan && taozhi1)
   {
      destruct(xan);
      destruct(taozhi);
      fpole = new(__DIR__"fpole");
      fpole->move(me);
      message_vision("$N用靈巧的雙手造成了一個別致的小魚杆。\n", me);
      destruct(this_object());
   }
   else
      message_vision("$N擺弄着手裏的細麻線。\n", me);
   return 1;
}

