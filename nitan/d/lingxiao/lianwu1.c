inherit ROOM;

void create()
{
        set("short", "練武廳");
        set("long", @LONG
這裡是凌霄城的練武場。場上放著幾個木人，是供凌霄弟子
練功之用。幾個凌霄弟子手持長劍，你來我往，正在場上練的起
勁。
LONG );
        set("exits", ([
            "east"      : __DIR__"fudian1",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "lingxiao" );
        setup();
        replace_program(ROOM);
}
