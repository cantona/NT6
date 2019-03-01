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
 //          "/quest/tulong/npc/hunter": 1, 
//          "/quest/tulong/npc/spirit1": 3,
 //          "/quest/tulong/obj/kaolu": 1,
        ]) );

        set("no_magic", 1);
        setup();
}
void init()
{
   add_action("do_west", "west");
   add_action("do_around", "around");

}

int do_around(string arg)
{
   object me, room;

   me = this_player(); 
   if (random(20)<10)
   { 
   tell_object(me, "你轉來轉去，也沒找到出口，你迷了路！！\n\n");
   room = find_object(__DIR__"spirit0");
   if(!objectp(room)) room=load_object(__DIR__"spirit0");
   me->move(room);
   return 1;
   }
   else  
   tell_object(me, "你發現西邊似乎有條路(west)。\n\n");
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
