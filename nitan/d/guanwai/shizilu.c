// /guanwai/shizilu.c

inherit ROOM;

void create()
{
        set("short", "石路");
        set("long", @LONG
這是一條碎石子舖的小路，西面煙霧繚繞的，牆壁都有些發黑了，
看上去有些刺眼，不過裡面卻飄來陣陣香氣，看來是廚房。東面則是
一個顯得有些荒涼的小院子，似乎沒什麼東西。時不時有一些胡家的
弟子匆匆而過。
LONG );
        set("exits", ([
                "south" : __DIR__"houyuan",
                "west"  : __DIR__"chufang",
                "east"  : __DIR__"taxue",
        ]));

        set("outdoors", "changbai");
        setup();
        replace_program(ROOM);
}