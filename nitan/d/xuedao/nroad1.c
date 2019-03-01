inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這是一條崎嶇的山路，馬隊到了這裡就不能在上去了。山路兩旁
雜草從生，路開始越來越難走。山路越走越窄，能隱隱望見前方又分
出了幾條叉路。
LONG );
        set("exits", ([
                "west"  : __DIR__"nroad2",
                "south" : __DIR__"nroad0",
                "north" : __DIR__"nroad5",
        ]));
        set("outdoors", "xuedao");
        setup();
        replace_program(ROOM);
}
