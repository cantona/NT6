// Room: /d/kunlun/nvwoshi.c
// Last Modified by winder on Nov. 15 2000

inherit ROOM;

void create()
{
        set("short","女弟子休息室");
        set("long",@LONG
這是間整潔的廂房，是崑崙派內女弟子們的休息室，因為門窗常閉
着，光線很昏暗。房裏放着幾張收拾得舒舒服服的木牀，看着就讓人想
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