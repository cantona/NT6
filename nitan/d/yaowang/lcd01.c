inherit ROOM;

void create()
{
        set("short", "泥濘小路");
        set("long", @LONG
這是一條的小岔路，地上總是像剛下過雨一樣泥濘不堪，和
著一些腐爛的枯枝敗葉，臭氣熏天。
LONG
        );
        set("exits", ([
  "southwest" : __DIR__"lcd02",
  "northeast" : "/d/foshan/nanling",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
