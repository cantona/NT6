inherit ROOM;

void create()
{
      set("short", "青石階");
        set("long", @LONG
已經是峨嵋山腳下了。南面一條通往峨嵋的青石階，兩旁綠樹蔭
蔽，空氣十分清新。西南方通向南詘的大理國。西邊好象有人搭了個
小草棚。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "northeast" : __DIR__"qsjie1",
          "southwest" : "/d/dali/road1",
          "southup"   : __DIR__"bgsgate",
          "west"      : __DIR__"caopeng",
      ]));
      set("no_clean_up", 0);
        set("coor/x", -370);
        set("coor/y", -200);
        set("coor/z", 0);
        setup();
      replace_program(ROOM);
}