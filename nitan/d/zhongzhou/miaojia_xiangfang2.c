inherit ROOM;

void create()
{
        set("short", "廂房");
        set("long", @LONG
這裏是苗家正廳旁的一個廂房，是供給遠來的客人和苗家弟子所
居住的。廂房中央擺着幾張大牀，幾張桌子。室中光線柔和，使人更
增睡意。
LONG );
        set("exits", ([
                "north" : __DIR__"miaojia_zhengting",
        ]));
        set("no_fight",1);
        set("no_steal",1);
        set("sleep_room",1);
        set("no_clean_up", 0);
        set("coor/x", -9010);
	set("coor/y", -970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}