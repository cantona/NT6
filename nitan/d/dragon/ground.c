#include <room.h>
inherit ROOM;

void init();
int do_climb(string arg);

void create()
{
      set("short","芳草地");
      set("long",
"芬芳的草地，到處是奇花異草。有一個參天大樹(tree)在草坪中央，\n"
"看起來似乎有一種神力。\n"
);
      set("exits",([ /* sizeof() == 1 */
          "southdown"  : __DIR__"bamboo1",
          "east"  : __DIR__"hole",
      ]));
      set("item_desc",([
                 "tree" :"紫色的樹身，堅硬無比，正是傳說中的人參果樹。\n"
      ]));
      set("objects", ([
  //       "/d/shenlong/obj/hua4" : 2,
      ]));
      set("no_magic", 1);
        setup();
      create_door("east", "石門", "west", DOOR_CLOSED);
}

void init()
{
        add_action("do_climb","climb");
}

int do_climb(string arg)
{
      object me;
      me = this_player();
      if (!arg || arg != "tree")
   {
            return notify_fail("你要爬什麼？\n");
    }
        if( query("qi", me)<70 )
                return notify_fail("你的氣不足，恐怕爬不上去。\n");
        if ((int)me->query_skill("dodge", 1) < 130)
{
          message_vision("$N想爬上樹去，可是爬到一半就一頭栽了下來。\n\n",me);
            me->receive_damage("qi",60);
         return 1;
}
else
          message_vision("$N脫掉鞋子，三下兩下就爬上了樹去。\n\n",me);
            me->receive_damage("qi",60);
                  me->move(__DIR__"tree");
       return 1;
}
