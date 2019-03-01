inherit ROOM;

void create()
{
        set("short", "湖邊小路");
        set("long", @LONG
這是聖湖邊的小路。長草越徑，蟲鳴陣陣，偶爾有白色水禽掠湖
點水，激起圈圈漣漪。
LONG );
        set("outdoors", "xuedao");
        set("exits", ([
                "east" : __DIR__"hubian3",
                "west" : __DIR__"hubian1",
        ]));
        setup();
        replace_program(ROOM);
}