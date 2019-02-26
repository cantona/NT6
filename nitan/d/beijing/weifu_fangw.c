inherit ROOM;

void create()
{
        set("short", "西廂房");
        set("long", @LONG
這裏是鹿鼎公府的西邊的一個廂房，是供給王府的客人所居住的。
廂房中央擺着幾張大牀，幾張桌子。室中光線柔和，使人更增睡意。
LONG );
        set("exits", ([
                "east" : "/d/beijing/weifu_dating",
        ]));

       set("no_fight",1);
       set("no_steal",1);
       set("sleep_room",1);
        set("no_clean_up", 0);
	set("coor/x", -2810);
	set("coor/y", 7710);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}