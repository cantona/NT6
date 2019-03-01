// /d/beihai/shiqiao.c
// Last Modified by winder on May. 22 2002

inherit ROOM;

void create()
{
        set("short", "石橋");
        set("long", @LONG
只是一座小石橋，連接了漪瀾堂和智珠殿。橋雖然不大，卻非常精
美。橋欄上雕刻了許多花草動物，栩栩如生。
LONG
        );
        set("exits", ([
                "southup"   : __DIR__"zhizhu",
                "northwest" : __DIR__"yilan",
        ]));
        set("outdoors", "beihai");
        set("no_clean_up", 0);

        set("coor/x", -180);
        set("coor/y", 4100);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}