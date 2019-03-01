inherit ROOM;

void create()
{
      set("short", "峨嵋寢宮");
        set("long", @LONG
這是峨嵋山金頂華藏庵外的一片小樹林峨嵋寢宮。
LONG );
      set("objects", ([
           CLASS_D("emei") + "/zhou" : 1,
      ]));
      set("exits", ([
          "south" : __DIR__"xiaoshulin4", 
      ]));
      setup();
      replace_program(ROOM);
}