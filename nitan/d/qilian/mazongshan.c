// Room: /d/qilian/mazongshan.c
// Winder 2000/09/05 

inherit ROOM;

void create()
{
        set("short", "馬鬃山");
        set("long", @LONG
馬鬃山狀如其名，山脈綿長，山峰岑差不齊，挽似野馬之鬃。聽老
人們講，凡心誠而善入山者，可得寶藏而歸，但凡為富不仁進山者，必
難生還。
LONG );
        set("outdoors", "qilian");
        set("exits", ([
                "southdown" : __DIR__"niaojutai",
                "west"      : __DIR__"qilianshan",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -11000);
        set("coor/y", 3000);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}