inherit ROOM;

void create()
{
      set("short", "青石階");
        set("long", @LONG
快到峨嵋山了。這是一條通往峨嵋山的青石階，兩旁綠樹廕庇，
空氣十分清新。時常能見到些遊人香客。
LONG );
      set("objects", ([
               __DIR__"npc/youngwoman": 1,
               __DIR__"npc/puren": 1,
      ]));
      set("outdoors", "emei");
      set("exits",([
          "north"      : __DIR__"xiaolu2",
          "west"       : "/d/chengdu/road1",
          "southwest"  : __DIR__"qsjie2",
      ]));
        set("coor/x", -360);
        set("coor/y", -190);
        set("coor/z", 0);
        setup();
      replace_program(ROOM);
}