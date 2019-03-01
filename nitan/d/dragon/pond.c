inherit ROOM; 
#include <ansi.h> 
void create()
{
   set("short", "池塘");
   set("long",
"[1;32m這是從三清湖引來的一個小小的池塘，一座小拱橋橫跨在池\n"
"塘上。塘水碧綠，上面有幾朵盛開的睡蓮，粉紅，潔白，鵝黃，襯托着碧\n"
"綠的葉子，漂浮在小池塘上，煞是惹人喜愛。一棵垂柳半橫在塘邊，柳絲\n"
"隨風飄舞。幾塊太湖石(stone)散落地放在池塘邊。\n"
);
   set("exits", ([ /* sizeof() == 4 */
      "southeast" : __DIR__"lake1",
   ]));
   
   set("item_desc", ([
      "太湖石": "幾塊玲瓏的太湖石，散落地放在池塘邊，石頭的一部分被埋在了土下。\n",
      "stone": "幾塊玲瓏的太湖石，散落地放在池塘邊，石頭的一部分被埋在了土下，看起來埋得不深，應該能夠推(push)得動。\n",
      "垂柳": "垂柳在不遠處的池塘邊，整個柳樹橫在池塘上。\n",
      "tree": "垂柳在不遠處的池塘邊，整個柳樹橫在池塘上。\n",
      "睡蓮": "半開的睡蓮象睡夢之中的美人，漂浮在碧綠的池塘上。\n",
      "flower": "半開的睡蓮象睡夢之中的美人，漂浮在碧綠的池塘上。\n",
   ]) );
      set("no_magic", 1);
        setup();
}

void init()
{
   add_action("do_push", "push");
}

int do_push(string arg)
{
   object me, qiuyin, where;
  
   me = this_player();
        where=environment(me); 
   if( query_temp("marks/moved", where))return notify_fail("石頭似乎被人推過，已經鬆動了。\n");
   if (!arg || arg != "stone" && arg != "石頭") 
      return notify_fail("你要推什麼 ? \n");
   message("vision",me->name()+"伸手推了推太湖石，石邊的土鬆動了，露出了一條胖胖的蚯蚓。\n", me);
   qiuyin = new("/quest/tulong/obj/qiuyin");
   qiuyin->move(where);
   set_temp("marks/moved", 1, where);
   return 1;

}
