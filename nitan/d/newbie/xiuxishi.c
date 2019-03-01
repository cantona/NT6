inherit ROOM;

void create()
{
        set("short", "休息室");
        set("long", @LONG
這是間整潔的廂房，因門窗常閉著，光線很昏暗。房裡別無他物，
只有中間放著一張收拾得舒舒服服的大床，看著就讓人想睡覺（輸入
指令 sleep）。
LONG);
        set("exits", ([
                "north" : __DIR__"lianwuchang",
        ]));

        set("xinshoucun", 1);
        set("no_clean_up", 0);
        set("sleep_room", 1);
        set("no_fight", 1);

        setup();

        replace_program(ROOM);
}