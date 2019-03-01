inherit ROOM; 
#include <ansi.h> 
void create()
{
        set("short", "山谷");
        set("long",
"[1;32m此處有些稀疏的樹木，眼前矗立著一座千層疊翠、萬裡點蒼\n"
"的山峰，圍成一處幽谷，中有一泓清潭，泉水從峰間奔流而下，噴珠泄玉，\n"
"直入清潭，還有幾只小精靈正在潭邊飛舞。此處空氣清涼濕潤，沁人心肺，\n"
"四周卻看不見任何明顯的出路，看來，你只好四處轉轉(around)看了。\n"
); 
        set("exits", ([
        ]) );

        set("objects", ([
//        "/quest/tulong/npc/spirit1": 4,
        ]) );

        set("no_magic", 1);
        setup();
}
void init()
{
   add_action("do_west", "xifang");
   add_action("do_catch", "catch");
   add_action("do_around", "around");

}

int do_around(string arg)
{
   object me, room;

   me = this_player(); 
   if (random(20)<10)
   { 
   tell_object(me, "你轉來轉去，也沒找到出口，你迷了路！！\n\n");
   room = find_object(__DIR__"liechang");
   if(!objectp(room)) room=load_object(__DIR__"liechang");
   me->move(room);
   return 1;
   }
   else  
     tell_object(me, "你發現西邊似乎有條路(xifang)。\n\n");
return 1;}

int do_catch(string arg)
{
   object spirit, me, room;

   me = this_player();
   if(!arg || arg != "小精靈" && arg != "spirit" ) return 0;
   spirit = present("spirit", this_object());
   if(!objectp(spirit)) return 0;

   switch ( random (7)) {
   case 0:
      message_vision("$N向前一撲！小精靈往後一閃，$N落了個空。 \n", me); 
      break;
   case 1:
      message_vision("$N向右一撲！小精靈向左一閃，$N落了個空。 \n", me); 
      break;
   case 2:
      message_vision("$N向左一撲，小精靈向右一閃，$N落了個空。\n", me); 
      break;
   case 3:
      message_vision("$N左撲右擋緊緊地跟著小精靈，深怕一轉眼就不見了……\n", me);
   break;
   case 4:
      message_vision("$N合身撲上，小精靈向旁邊一晃躲開了$N，$N收勢不住摔了個嘴啃泥。  \n", me);
   break;
   case 5:
      message_vision("$N躡手躡腳地朝小精靈摸過去，想從後面抓住它，小精靈機靈地向前一沖，$N沒成功。\n", me);
   break;
   case 6:
      message_vision("$N往前一撲，小精靈向前一沖，從$N的手邊飛快的飛了過去。 \n", me); 
      message_vision("$N調頭便向小精靈逃跑的方向追去……\n", me); 
      message_vision("\n小精靈三轉兩轉，倏地一下不見了蹤影。\n\n", me); 
      message("vision", me->name() + "緊緊跟著小精靈倏地一下也不見了蹤影。\n", environment(me), me);
      room = find_object(__DIR__"outlet2");
      if(!objectp(room)) room=load_object(__DIR__"outlet2");
      me->move(room);
      destruct(spirit);
      break;
   }

   return 1;
}

int do_west(string arg)
{
        object me;
        object room;
        me = this_player();
        message_vision("$N往西邊的樹林走去 . \n", me);

        room = load_object(__DIR__"spirit3");
        if(room) me->move(room);

        return 1;
}
