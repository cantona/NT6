// dongmen.c 洞門

inherit ROOM;

void create()
{
        set("short", "洞門");
        set("long", @LONG
你的面前突然一亮，眼前赫然出現一道玉石砌成的洞門，門額
上雕有三個大字迎賓館，兩旁石粱雕龍刻鳳，不知凝聚着多少名工
巧匠的心血哇！更體現出主人的富有和奢侈。
LONG );
        set("exits", ([
                "enter" : __DIR__"yingbin",
                "west" : __DIR__"shidong1",
        ]));
        set("objects", ([
                __DIR__"npc/dizi1" : 1]));
        set("coor/x", -3090);
        set("coor/y", -22080);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}