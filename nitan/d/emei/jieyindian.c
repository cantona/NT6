inherit ROOM;

void create()
{
      set("short", "接引殿");
        set("long", @LONG
接引殿右邊瀕崖，是金鋼嘴。崖下有一塊巨石，形狀似鐘故名「
鐘石」。對面有一石，高聳十余丈，叫仙人石。由此向上仰攀即到萬
行庵，北下經「八十四盤」至洗象池。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "northwest" : __DIR__"bashisipan3",
          "westup"    : __DIR__"wanxingan",
      ]));
      set("no_clean_up", 0);
        set("coor/x", -560);
        set("coor/y", -300);
        set("coor/z", 200);
        setup();
      replace_program(ROOM);
}