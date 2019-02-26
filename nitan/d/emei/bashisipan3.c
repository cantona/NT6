inherit ROOM;

void create()
{
      set("short", "八十四盤");
        set("long", @LONG
八十四盤，道路艱險陡峭，迂迴盤折，令人不能喘息。路左是蔽
日遮天的冷杉林，路右是深不見底的絕壁峽谷。由此往上至接引殿，
北下到洗象池。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "northdown"  : __DIR__"bashisipan2",
          "southeast"  : __DIR__"jieyindian",
          "northeast"  : __DIR__"lengsl4",
      ]));
        set("coor/x", -570);
        set("coor/y", -290);
        set("coor/z", 200);
        setup();
      replace_program(ROOM);
}