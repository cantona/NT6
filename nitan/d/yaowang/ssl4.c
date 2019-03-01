inherit ROOM;

void create()
{
        set("short", "碎石路");
        set("long", @LONG
這是一條用五彩的碎石子舖成的小路靜靜的東面延伸，路邊
是輕輕的嫩草，路的兩旁各有一個小花壇，裡面開著艷麗的花朵。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "east" : __DIR__"jiaomen",
  "west" : __DIR__"ssl3",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
