// /guanwai/houyuan.c

inherit ROOM;

void create()
{
    set("short", "後院");
    set("long", @LONG
這是胡家的後院，雖然不大，但是收拾得頗為整齊利落，看來是
有人常用心打掃的緣故。東面隱隱的傳來打鬥聲，西面靜一些。而北
面望過去是一條舖滿碎石子的小路，隱隱飄來陣陣飯香。
LONG );
    set("exits", ([
        "south" : __DIR__"xiaowu",
        "north" : __DIR__"shizilu",
        "west"  : __DIR__"jingxiu",
    ]));
    set("outdoors", "changbai");
    setup();
        replace_program(ROOM);
}