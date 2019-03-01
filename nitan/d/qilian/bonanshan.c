// Room: /d/qilian/bonanshan.c
// Winder 2000/09/05 

inherit ROOM;

void create()
{
        set("short", "博南山");
        set("long", @LONG
往北走，地面已漸漸地不再平坦，由丘陵地區轉入山區。大路到此
就中斷了，只剩坎坷不平的山路。再往北就是祁連山。東面是通向蘭州
官道。
LONG );
        set("outdoors", "qilian");
        set("no_clean_up", 0);
        set("exits", ([
                "eastdown" : "/d/xingxiu/xxroad2",
                "north"    : __DIR__"bulangpo1",
        ]));
        set("coor/x", -9900);
        set("coor/y", 2700);
        set("coor/z", 60);
        setup();
        replace_program(ROOM);
}