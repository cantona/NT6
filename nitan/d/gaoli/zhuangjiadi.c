
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "莊稼地");
        set("long", @LONG
這裡是一片莊稼地。田地不大，但是莊稼看起來長的很好。有幾個
小孩在旁邊玩耍。遠處有幾個農夫在那裡種田。一陣清風吹來，田野的
氣息不禁讓你心曠神怡。田地旁邊放著幾個草人，不知道踢幾下會怎麼
樣。
LONG
);
        set("exits",([
        "southup" : __DIR__"xiaolu2",
        
        ]));
set("outdoors","gaoli");
        setup();
//        replace_program(ROOM);
}

void init()
{
   add_action("do_ci","ti");
}

int do_ci(string arg)
{
   object me;
   me=this_player();
   if(!arg||arg!="草人")
   return notify_fail("你要踢什麼？\n");
  
   if(me->query("sen")<20)
   return notify_fail("你精神太差了！\n");
   if(me->query_skill("leg",1)>=101)
   return notify_fail("一個農夫跑了過來：嘿，不要亂碰我的草人！\n");
   if(me->is_busy())
   return notify_fail("你正忙著呢！\n");
   
   message_vision(YEL"$N一轉身，然後抬腿朝草人踢去！\n"NOR,me);
   me->improve_skill("leg",me->query_int()/2+20+random(5));
   me->add("sen",-20);
   if(me->query_skill("leg",1)<50)
   message_vision("$N下盤不穩，險些跌倒！\n",me);
   else if(me->query_skill("leg",1)<100)
   message_vision("$N收勢站好，微微一笑。\n",me);
   else if(me->query_skill("leg",1)<150)
   message_vision("$N瀟洒的一個轉身，輕輕收勢站好！\n",me);
  
   return 1;
}
