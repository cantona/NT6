// Room: /d/huangshan/guangming.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "光明頂");
        set("long", @LONG
光明頂是第二高峰，因為多次出現佛光，所以被稱為光明頂，光明
頂上起伏平緩，面積廣大，古人曾形容它“形若覆巢，旁無依附，秋水
銀河，長空一色”。這裡是看日出，觀雲海的最佳場所，如果機緣巧合，
還可以看見難得一遇的佛光。
LONG
        );
        set("exits", ([ 
                "west"    : __DIR__"feilai",
                "southup" : __DIR__"lianhua",
        ]));
        set("objects", ([
                __DIR__"npc/monk" : 1,
        ]) );
        set("outdoors", "huangshan");
        set("coor/x", -595);
        set("coor/y", -1030);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}