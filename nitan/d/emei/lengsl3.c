inherit ROOM;

void create()
{
      set("short", "冷杉林");
        set("long", @LONG
這是片遮天蔽日的冷杉林。數人也合抱不過來的冷杉樹簇在一塊，
枝繁葉茂，象一蓬蓬巨傘恆伸向天空，把陽光遮得絲毫也無。看地上
厚厚的枯枝爛葉，顯然遊客很少踏足此處。
LONG );
      set("exits", ([
          "west"      : __DIR__"bashisipan2",
          "northeast" : __DIR__"lengsl2",
          "southup"   : __DIR__"lengsl4",
      ]));
      set("no_clean_up", 0);
      set("coor/x", -560);
        set("coor/y", -280);
        set("coor/z", 190);
        set("coor/x", -560);
        set("coor/y", -280);
        set("coor/z", 190);
        setup();
      replace_program(ROOM);
}