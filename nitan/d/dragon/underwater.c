inherit ROOM; 
#include <ansi.h> 
void create()
{
        set("short", "潭下");
        set("long",
"[1;32m潭水很深，冰涼的潭水浸得你骨頭都發麻，一只隨你一快兒\n"
"掉下來的朽木一起一伏，在水中盪漾。一線天光從你頭頂上射下來，那樣\n"
"微弱，你都不知道還有沒有生還的機會……不過，還是想法子往上爬(cli\n"
"mb)吧。\n"
);
        set("no_magic", 1);
        setup();
}

void init()
{
   add_action("do_climb", "climb");
   if(interactive(this_player()))
   call_out("do_flush",60,this_player());
}

int do_climb(string arg)
{
   object me, room;

   me = this_player();
   if(me->is_busy())
        return notify_fail("你現在沒空！\n");
   switch (random(3)) {
   case 0:
      message_vision("$N手腳並用地往上爬，才爬到一半，一失手又摔了下來。\n", me);
      me->receive_damage("jing",20);
        me->start_busy(5);
      break;
   case 1:
      message_vision("$N手腳並用地往上爬，眼看快到頭了，結果一失手又摔了下來。\n", me);
      me->receive_damage("jing",40);
        me->start_busy(5);
      break;
   case 2:
      if(!arg || arg != "上" && arg != "up" ) return 0;
     room = find_object(__DIR__"spirit9");
     if(!objectp(room)) room=load_object(__DIR__"spirit9");
      me->move(room);
      message_vision("$N渾身濕淋淋地從水中爬了上來。\n", me);
      break;
   }
   return 1;
}

void do_flush(object me)
{
   object room;

   if(!me || environment(me) != this_object())
   return;
   tell_object(me,"\n你突然發覺潭裡的水居然在流動！\n\n");
   tell_object(me,"水流好象帶著你從潭底的一個暗道裡湧出……\n");
   tell_object(me,"你陷入一片完全的黑暗之中，心中充滿了恐懼……\n\n");
    room = find_object(__DIR__"lake");
    if(!objectp(room)) room= load_object(__DIR__"lake");
   me->move(room);
   tell_object(me,"不知道過了多久，你眼前一亮，被水流帶出了湖面。\n\n");
}

