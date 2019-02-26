inherit ROOM;

void create()
{
      set("short", "休息室");
        set("long", @LONG
這裏是峨嵋華藏庵的休息室。窗簾拉下來，房裏整整齊齊放了很
多木牀。有幾個夜晚守庵的小師太正在睡覺。休息室外就是禪房。
LONG );
      set("exits", ([
          "north" : __DIR__"hcachanfang", 
      ]));
      set("no_fight", 1);
      set("sleep_room", 1);
      set("no_clean_up", 0);
      setup();
      replace_program(ROOM);
}