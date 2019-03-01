inherit ROOM;

void create()
{
      set("short", "靈文閣");
        set("long", @LONG
這裡是福壽庵的靈文閣，是主持靜照師太傳授佛法的地方。兩名
青衣小尼姑隨侍在旁，似乎在聆聽師太的教晦。閣內布置簡陋，靠牆
放著幾把竹椅，地上放著幾個蒲團。東首有一禪房。西面是一個齋廳。
LONG );
      set("objects", ([
           CLASS_D("emei") + "/zhao" : 1,
      ]));
      set("exits", ([
          "out"  : __DIR__"fushouan",
          "east" : __DIR__"fsachanfang",
          "west" : __DIR__"fsazhaitang",
      ]));
        set("coor/x", -440);
        set("coor/y", -240);
        set("coor/z", 70);
        setup();
      replace_program(ROOM);
}