inherit ROOM;

void create()
{
      set("short", "大殿");
        set("long", @LONG
千佛庵內殿宇高廣宏闊，清潔莊嚴。庵內有一具七萬千佛蓮燈，
有紋龍七條環于燈體，並有佛像數百周匝排列，雕縷精致無比。
LONG );
      set("objects", ([
           CLASS_D("emei") + "/hui" : 1,
           CLASS_D("emei") + "/wenyin" : 1,
      ]));
      set("exits", ([
          "out"  : __DIR__"qianfoan",
          "east" : __DIR__"qfachanfang",
      ]));
      set("coor/x", -470);
        set("coor/y", -240);
        set("coor/z", 100);
        set("coor/x", -470);
        set("coor/y", -240);
        set("coor/z", 100);
        setup();
      replace_program(ROOM);
}