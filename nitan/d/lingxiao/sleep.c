inherit ROOM;

void create()
{
        set("short", "休息室");
        set("long", @LONG
這是間整潔的廂房，門窗常閉，光線昏暗。房裡別無他物，
只有兩邊放著幾張收拾得舒舒服服的大床，看著就讓人想睡覺。
LONG );
        set("sleep_room", 1);
        set("no_clean_up", 0); 
        set("no_fight", 1);
        set("exits", ([
                "east" : __DIR__"zoulang1",
        ]));
        setup();
        replace_program(ROOM);
}
