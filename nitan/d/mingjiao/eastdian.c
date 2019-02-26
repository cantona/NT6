//room: /d/mingjiao/eastdian.c
inherit ROOM;

void init();

void create()
{
        set("short","明教東側殿");
        set("long", @LONG
這裏是東側殿，是接待來賓的地方。殿內擺着幾張桌子，桌旁圍
放數把椅子。牆上懸着幾幅字畫，牆邊一排書架，架上擺滿書籍。窗
外是茫茫崑崙雪山，雪峯延綿。
LONG );
       set("exits",([
           "west"     : __DIR__"qiandian",
       ]));
       set("no_clean_up", 0);
       setup();
       replace_program(ROOM);
}
