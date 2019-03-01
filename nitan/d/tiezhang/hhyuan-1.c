// Room: /u/zqb/tiezhang/hhyuan-1.c

inherit ROOM;

void create()
{
        set("short", "後花園");
        set("long", @LONG
這是一處環境優雅的花園。只見喬鬆修竹，蒼翠蔽天，層巒奇岫，靜窈
幽深。西面有一座假山，東面是大片的花圃。北面是通往山上的路。
LONG        );
        set("exits", ([ /* sizeof() == 4 */
  "north" : __DIR__"shanlu-3",
  "south" : __DIR__"hxfang",
  "west" : __DIR__"hhyuan-3",
  "east" : __DIR__"hhyang-2",
]));
        set("no_clean_up", 0);
        set("outdoors", "tiezhang");

        setup();
        replace_program(ROOM);
}