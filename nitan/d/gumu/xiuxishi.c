// xiuxishi.c 休息室
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "休息室");
        set("long", @LONG
這是間很大的房間，光線非常昏暗。房裡沒有什麼別的東西，只有
中間一張小桌，裡牆放著一張收拾得舒舒服服的大床，床上的被褥也整
理得整整潔潔的，看著就讓人想睡覺。
LONG        );
        set("exits", ([
                "east" : __DIR__"mudao02",
        ]));
        set("sleep_room",1);
        set("no_fight",1);
        set("no_steal",1);
        set("no_clean_up", 0);
        set("coor/x", -3240);
        set("coor/y", 10);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}