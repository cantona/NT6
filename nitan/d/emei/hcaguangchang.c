inherit ROOM;

void create()
{
      set("short","華藏庵廣場");
        set("long", @LONG
這裏是峨嵋華藏庵的廣場，地上鋪着青磚。正前方有一道台階，
通往大雄寶殿。殿前有個丈許高的大香爐，香爐前的香台上，紅燭高
燒，香煙飄繞。廣場上幾個小師太正在練功。自此左右各有一條走廊
通向後殿。
LONG );
              set("objects", ([
                CLASS_D("emei") + "/first" : 1,
                   CLASS_D("emei") + "/xu" : 1,
              ]));

              set("outdoors", "emei");

              set("exits", ([
                  "north" : __DIR__"hcazhengdian", 
                  "south" : __DIR__"hcadadian", 
                  "west"  : __DIR__"hcawest1", 
                  "east"  : __DIR__"hcaeast1", 
              ]));

              set("valid_startroom", 1);

              set("coor/x", -560);
        set("coor/y", -330);
        set("coor/z", 220);
        setup();
              replace_program(ROOM);
              "/clone/board/emei_b"->foo();
}
