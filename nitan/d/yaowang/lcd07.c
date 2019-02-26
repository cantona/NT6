inherit ROOM;

void create()
{
        set("short", "石板路");
        set("long", @LONG
這是一條青石板鋪的小路，路的兩旁還各有一道低矮的石欄
杆，外面是輕輕的嫩草地。西面不遠隱約是一幢高大的門樓。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "west" : __DIR__"door",
  "east" : __DIR__"lcd06",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
