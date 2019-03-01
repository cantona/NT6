inherit ROOM;

void create()
{
        set("short", "碎石路");
        set("long", @LONG
這是一條用五彩的碎石子舖成的小路靜靜的東面延伸，路邊
是輕輕的嫩草，路的兩旁各有一個小花壇，裡面開著艷麗的花朵。
西面是一個大空場。北面是一排青磚瓦房。
LONG
        );
        set("exits", ([
  "north" : __DIR__"sleeproom",
  "east" : __DIR__"ssl3",
  "west" : __DIR__"myuan",
]));

        set("outdoors", "yaowang");
        setup();
}

int valid_leave(object ob,string dir)
{
        if( !wizardp(ob)
        && (dir == "north")
         && (query("family/family_name", ob) != "藥王谷") )
                return notify_fail("邊上竄出兩個童子攔住了你的去路。\n");

        return ::valid_leave(ob,dir);
}
