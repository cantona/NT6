// Room: /d/huijiang/bingqi.c
// Last Modified by winder on Sep. 12 2001

inherit ROOM;

void create()
{
        set("short", "兵器庫");
        set("long",@LONG
這裡是紅花會的兵器庫，一捆捆的兵器堆得海了。清兵屢次進犯回
疆，交戰頻仍，這裡很多兵器都是萬裡迢迢外的中原麻煩清兵帶來的。
LONG );
        set("objects", ([
                WEAPON_DIR"zhujian"     : random(2)+1,
                WEAPON_DIR"zhubang"     : random(2)+1,
                WEAPON_DIR"blade/mudao" : random(2)+1,
                __DIR__"obj/feidao"     : random(2)+1,
        ]));
        set("exits", ([
                "west" : __DIR__"wuchang",
        ]));
        set("coor/x", -50030);
        set("coor/y", 9140);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}