// Room: /d/yueyang/xiangfeici2.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "湘妃祠前殿");
        set("long", @LONG
前殿是這個三進湘妃祠的第二進，有武將鎮守，兩邊是廂房。金字
垛的騎馬牆，上雕有蝙蝠壽桃，蝠是福的同聲，為福壽的意思，
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "south" : __DIR__"xiangfeici1",
                "north" : __DIR__"xiangfeici3",
        ]));
        set("coor/x", -1660);
        set("coor/y", 2320);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}