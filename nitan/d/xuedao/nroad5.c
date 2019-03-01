inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這是一條崎嶇的山路，馬隊到了這裡就不能在上去了。山路兩旁
雜草從生，路開始越來越難走。
LONG );
        set("exits", ([
                "north" : __DIR__"nroad6",
                "south" : __DIR__"nroad1",
        ]));
        set("objects",([
                "/clone/quarry/ying" : 1,
        ]));
        set("outdoors", "xuedao");
        setup();
        replace_program(ROOM);
}
