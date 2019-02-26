inherit ROOM;

void create()
{
        set("short", "議事廳");
        set("long", @LONG
這裏就是藥王谷的議事廳。高大的殿堂，四處雕樑畫棟。
正中是一把巨大的紅木太師椅，後面一扇巨大的屏風上
雕刻着蟠龍飛鳳。
LONG
        );
        set("exits", ([
  "south" : __DIR__"myuan",
  "north" : __DIR__"xiangfang",
]));
/*
        set("objects", ([
        CLASS_D("yaowang") + "/wuchen" : 1,
]));
*/
        setup();
        replace_program(ROOM);
}
