// Last Modified by Sir on May. 22 2001
// xiuxishi.c 休息室

inherit ROOM;

void create()
{
        set("short", "休息室");
        set("long", @LONG
這裏是恆山白雲庵的休息室。光線非常昏暗。房裏沒有什麼別的東
西，只有中間放着一張收拾得舒舒服服的大牀，有幾個夜晚守庵的小師
太正在睡覺。
LONG
        );
        set("exits", ([
                "east" : __DIR__"byawest",                
        ]));
        set("no_clean_up", 0);
        set("sleep_room",1);
        set("no_beg",1);
        set("no_fight",1);
        set("no_steal",1);

        set("coor/x", 20);
        set("coor/y", 3210);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}
