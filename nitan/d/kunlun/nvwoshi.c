// Room: /d/kunlun/nvwoshi.c
// Last Modified by winder on Nov. 15 2000

inherit ROOM;

void create()
{
        set("short","女弟子休息室");
        set("long",@LONG
這是間整潔的廂房，是昆侖派內女弟子們的休息室，因為門窗常閉
著，光線很昏暗。房裡放著幾張收拾得舒舒服服的木床，看著就讓人想
睡覺。
LONG
);
        set("exits",([
                "northwest" : __DIR__"jiuqulang2",
        ]) );
        set("no_clean_up",0);
        set("no_fight", 1);
        set("sleep_room", 1);
        set("coor/x", -119970);
        set("coor/y", 40080);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}