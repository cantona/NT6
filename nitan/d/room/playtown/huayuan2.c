// Room: /d/playertown/huayuan2.c 花園
// Build 1999.12.10 bmw

inherit ROOM;

void create()
{
        set("short", "花園");
        set("long",
"你走在一條青磚小道上，兩邊整整齊齊地排着兩排楊柳，湖上總有幾\n"
"艘漁船正在打漁，漁夫們歡快地唱着歌，拖起一網活蹦亂跳的魚兒。湖畔\n"
"邊上是一片片翠綠的草坪，上面幾對夫婦正相依在那，低頭吟語着，偶爾\n"
"還傳來一陣澀笑。\n"
);
        set("outdoors", "playertown");
//      set("no_clean_up", 0);
        set("exits", ([
                "east"  :        __DIR__"huayuan3",
                "south"        :        __DIR__"huayuan1",
        ]));
        setup();
        replace_program(ROOM);
}