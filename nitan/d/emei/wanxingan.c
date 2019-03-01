inherit ROOM;

void create()
{
      set("short", "萬行庵");
        set("long", @LONG
太子坪萬行庵是古智禪師創建。庵外滿山長滿莎欏花，花數芭合
成一朵，葉包在花外，古人以其根堅難易而盛讚，以喻潔身自好之高
貴品質。由此向南上便至金頂，下至接引殿。
LONG );
      set("objects", ([
           CLASS_D("emei") + "/jia" : 1,
      ]));
      set("outdoors", "emei");
      set("exits", ([
          "eastdown"  : __DIR__"jieyindian",
          "southup"   : __DIR__"jinding",
      ]));
      set("coor/x", -570);
        set("coor/y", -300);
        set("coor/z", 210);
        setup();
      replace_program(ROOM);
}