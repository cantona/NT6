inherit ROOM;

void create()
{
        set("short", "碎石路");
        set("long", @LONG
這是一條用五彩的碎石子鋪成幽靜的小路，路邊是輕輕的嫩
草，路的兩旁各有一個小花壇，裏面開着豔麗的花朵。西面是一
個小月門，東面是一個大空場。
LONG
        );
        set("exits", ([
  "east" : __DIR__"myuan",
  "out" : __DIR__"hqdoor",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
