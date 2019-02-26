// Room: /d/huijiang/wuchang.c
// Last Modified by winder on Sep. 12 2001

inherit ROOM;

void create()
{
        set("short", "練武場");
        set("long",@LONG
這裏是紅花會的練武場，不少紅花會的會眾正在練功。場子中央豎
着幾個木人，場子周圍擺着些沙袋、兵器等物。看來反清復明、恢復故
國衣冠也實在不是一件容易的事。
LONG );
        set("outdoors", "huijiang");        
        set("objects", ([
                "/d/shaolin/npc/mu-ren" : 5,
        ]));
        set("exits", ([
                "east"     : __DIR__"bingqi",
                "north"    : __DIR__"fangju",
                "south"    : __DIR__"xingtang",
                "west"     : __DIR__"zoulang3",
        ]));
        set("coor/x", -50040);
        set("coor/y", 9140);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}