inherit ROOM;

void create()
{
      set("short", "二天門");
        set("long", @LONG
這裏是「二天門」，金光燦燦的金頂就在眼前了。
LONG );
      set("exits", ([
          "northdown": __DIR__"toutiangate",
          "southup"  : __DIR__"santiangate",
      ]));
      set("outdoors", "wudang");
      set("no_clean_up", 0);
        set("coor/x", -350);
        set("coor/y", -400);
        set("coor/z", 160);
        setup();
      replace_program(ROOM);
}