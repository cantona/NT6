inherit ROOM;

void create()
{
      set("short", "神水庵");
        set("long", @LONG
神水庵位于寶掌峰下，庵前有大峨石和玉液泉，泉出石下清澈無
比，終年不涸。一株大海棠樹已是數百蒼齡，抱可數圍高達十余丈。
旁邊有福壽庵；由此西上中峰寺東下純陽殿。
LONG );
      set("exits", ([
          "eastdown"  : __DIR__"chunyangdian",
          "westup"    : __DIR__"zhongfengsi",
          "south"     : __DIR__"fushouan",
      ]));
      set("outdoors", "emei");
      set("no_clean_up", 0);
        set("coor/x", -440);
        set("coor/y", -230);
        set("coor/z", 70);
        setup();
      replace_program(ROOM);
}