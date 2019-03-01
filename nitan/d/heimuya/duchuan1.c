// Room: /d/shaolin/duchuan1.c

inherit ROOM;

void create()
{
        set("short", "渡船");
        set("long", @LONG
一葉小舟，一次就能載七、八個人。一名三十多歲日月教徒裝扮
的艄公手持長竹篙，正在船尾撐著船，這艄公臂力驚人，小舟在他的
操控之下，一支箭般飛快地射向對岸。
LONG );
        set("no_clean_up", 0);
        set("outdoors", "heimuya");
        setup();
        replace_program(ROOM);
}
