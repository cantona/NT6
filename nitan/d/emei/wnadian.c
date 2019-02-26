inherit ROOM;

void create()
{
      set("short", "萬年庵磚殿");
        set("long", @LONG
這裏是萬年庵的拱頂無樑磚殿。磚殿四壁為正方形，頂為穹窿圓
拱形，殿內有普賢菩薩騎六牙白象的銅鑄像一尊。拱頂無樑磚殿四壁
下方，有小龕二十四，內各供鐵鑄佛像一尊。四壁上方則有橫龕六道，
列置銅鑄小佛三百零七個。
LONG );
      set("objects", ([
           CLASS_D("emei") + "/kong" : 1,
           CLASS_D("emei") + "/wenfang" : 1,
      ]));
      set("exits", ([
          "east"    : __DIR__"wnachanfang",
          "out"     : __DIR__"wannianan",
      ]));
        set("coor/x", -470);
        set("coor/y", -220);
        set("coor/z", 90);
        setup();
      replace_program(ROOM);
}