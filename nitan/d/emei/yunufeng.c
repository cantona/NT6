inherit ROOM;

void create()
{
      set("short", "玉女峯");
        set("long", @LONG
這是歸雲閣邊的玉女峯，峯頂有一個四尺見方的小池，深亦四尺，
四季不枯，傳為天女沐浴之器。古時州刺史馮楫，曾在此結茅而居，
發奮誦讀「華嚴經」，不食人間煙火，於是玉女下凡，為他饋贈食物。
LONG );
      set("objects", ([
           CLASS_D("emei") + "/fang" : 1,
      ]));
      set("exits", ([
          "northdown"  : __DIR__"guiyunge",
      ]));
      set("outdoors", "emei");
      setup();
      replace_program(ROOM);
}