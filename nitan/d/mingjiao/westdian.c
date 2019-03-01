//room: /d/mingjiao/westdian.c
inherit ROOM;

void init();

void create()
{
        set("short","明教西側殿");
        set("long", @LONG
這裡是西側殿，是接待來賓的地方。殿內擺著幾張桌子，桌旁圍
放數把椅子。牆上懸著幾張硬弓，甚是雄壯，旁邊堆著一堆羽箭。窗
外是茫茫昆侖雪山，雪峰延綿。
LONG );
       set("exits",([
           "east"     : __DIR__"qiandian",
       ]));
       set("no_clean_up", 0);
       setup();
       replace_program(ROOM);
}
