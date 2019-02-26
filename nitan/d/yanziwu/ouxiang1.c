// Room: /d/yanziwu/ouxiang1.c
// Date: Jan.28 2000 by Winder

inherit ROOM;

void create()
{
        set("short", "藕香小築");
        set("long", @LONG
藕香小築建得小巧玲瓏。小築四周栽滿了湘妃竹，湖面和風催動，
頓時就嘩啦啦響成一片。這裏是蔓陀山莊大小姐的閨房。小築正中放着
一張小几。幾邊是一大塊地毯，墊着兩個蒲團。四壁清冷，渾不似女孩
兒家的閨房。
LONG );
        set("exits", ([
                "northeast" : __DIR__"path17",
                "south"     : __DIR__"path18",
                "up"        : __DIR__"ouxiang2",
        ]));
        set("objects", ([
                __DIR__"npc/youcao" : 1,
        ]));
        set("coor/x", 1200);
        set("coor/y", -1230);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}