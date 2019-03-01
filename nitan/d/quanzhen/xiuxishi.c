// xiuxishi.c 休息室
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "休息室");
        set("long", @LONG
這是間很大的房間，光線非常昏暗。房裡沒有什麼別的東西，
只有中間放著一張收拾得舒舒服服的大床，床上的被褥也整理得
整整潔潔，看著就讓人想睡覺。
LONG
        );

        set("exits", ([
                "west" : __DIR__"wuchang2",
                "northwest" : __DIR__"wuchang1",
                "south" : __DIR__"shantang",
        ]));
        set("no_clean_up", 0);
        set("sleep_room",1);
        set("no_beg",1);
        set("no_fight",1);
        set("no_steal",1);

        set("coor/x", -2740);
        set("coor/y", 90);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}