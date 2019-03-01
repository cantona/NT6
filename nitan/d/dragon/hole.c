#include <room.h>
inherit ROOM;

void create()
{
      set("short","凌雲窟");
      set("long",
"祥雲光滿，瑞靄香浮。在這處遠山裡居然還有如此仙境。這裡正是獨\n"
"立雲海，傲越千山的玄女峰。而這個深陷入巖壁的洞窟，似乎隱藏著什麼\n"
"秘密呢。\n"
);
      set("exits",([ /* sizeof() == 1 */
//          "up"  : "/d/xuansu/shanjiao",
          "west"  : __DIR__"ground",
      ]));
      set("objects",([
//                 "/d/xuansu/npc/qilin" : 1,
      ]));
      set("no_magic", 1);
        setup();
      create_door("west", "石門", "east", DOOR_CLOSED);
}
