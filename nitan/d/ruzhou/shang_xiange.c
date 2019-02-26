inherit ROOM;

void create()
{
        set("short", "東廂房");
        set("long", @LONG
這裏是商家堡後廳東側的一個廂房，是供給遠來的客人和商
家弟子所居住的。廂房中央擺着幾張大牀，幾張桌子。室中光線
柔和，使人更增睡意。
LONG);
        set("exits", ([
                "west"  : __DIR__"shang_houting",
        ]));
        set("no_fight",1);
        set("no_steal",1);
        set("sleep_room",1);
        set("no_clean_up", 0);
	set("coor/x", -6740);
	set("coor/y", 1890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}