// Room: /d/huangshan/xuanyuan.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "軒轅峰");
        set("long", @LONG
這是黃山後山東的最高峰，因一路怪石嶙峋，加之前面採石峰異常
難行，所以很少人煙。據說這裡便是黃帝得道飛升的所在，也不知真假
但是至今留有許多道家遺跡，可見確有人在此修道。
LONG
// 南邊有一矮峰，上面居然隱約有一茅廬，似乎有人居住，兩峰之間僅有一根鐵索。
        );
        set("exits", ([ 
                "west" : __DIR__"caishi",
//                "east" : __DIR__"tiesuo",
        ]));
        set("outdoors", "huangshan");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}