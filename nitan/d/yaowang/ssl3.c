inherit ROOM;

void create()
{
        set("short", "碎石路");
        set("long", @LONG
這是一條用五彩的碎石子鋪成的小路靜靜的東面延伸，路邊
是輕輕的嫩草，路的兩旁各有一個小花壇，裏面開着豔麗的花朵。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "east" : __DIR__"ssl4",
  "west" : __DIR__"ssl2",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
