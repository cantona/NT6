// 綠洲

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "回疆綠洲" NOR);
        set("long", @LONG
在戈壁的盡頭出現了一個綠洲。這裡有口水井，可是已經幹涸了。
LONG);
        set("no_sleep_room", 1);
        set("valid_startroom", 1);

        set("objects", ([
                    __DIR__"obj/hamigua" : 2

        ]));
 
        set("exits", ([
              "northwest" : __DIR__"gebi1",
              "southeast" : __DIR__"gebi2",
              "southwest" : __DIR__"gebi3",
              "northeast" : __DIR__"gebi4",
        ]));

        set("outdoors", "hasake");
        set("no_quest",1);
        setup(); 

}

void init()
{
       object me = this_player();
      if(objectp(present("shou juan", me))){
       switch(random(4)) {
       case 0 :
               set_temp("gc1_n", 1, me);
               tell_object(me, HIC "突然從手絹上顯出一條指向北面的細線來。\n" NOR);          
               break;
       case 1 :
               set_temp("gc1_s", 1, me);
               tell_object(me, HIC "突然從手絹上顯出一條指向南面的細線來。\n" NOR);
               break;
       case 2 :
               set_temp("gc1_e", 1, me);
               tell_object(me, HIC "突然從手絹上顯出一條指向東面的細線來。\n" NOR);
               break;
       case 3 :
               set_temp("gc1_w", 1, me);
               tell_object(me, HIC "突然從手絹上顯出一條指向西面的細線來。\n" NOR);
               break;
       }
    }             
}