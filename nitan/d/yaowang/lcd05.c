inherit ROOM;

void create()
{
        set("short", "石板路");
        set("long", @LONG
這是一條青石板舖的小路，路的兩旁還各有一道低矮的石欄
桿，外面是輕輕的嫩草地。
LONG
        );
        set("outdoors", "yaowang");
        set("exits", ([ /* sizeof() == 2 */
  "west" : __DIR__"lcd06",
  "east" : __DIR__"lcd04",
]));

        setup();
        replace_program(ROOM);
}
