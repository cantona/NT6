inherit ROOM;

void create()
{
      set("short", "歸雲閣");
        set("long", @LONG
歸雲閣，原是唐代福昌達道禪師的道場。宋代紹興年間僧人士性
又率眾重建。歸雲閣左有玉女峯，西上可抵純陽殿，東下是觀音堂。
LONG );
      set("objects", ([
           __DIR__"npc/boydizi" : 1,
           __DIR__"npc/girldizi" : 1,
      ]));
      set("exits", ([
          "eastdown"  : __DIR__"guanyintang",
          "westup"    : __DIR__"chunyangdian",
          "southup"   : __DIR__"yunufeng",
      ]));
      set("outdoors", "emei");
        set("coor/x", -420);
        set("coor/y", -230);
        set("coor/z", 50);
        setup();
      replace_program(ROOM);
}