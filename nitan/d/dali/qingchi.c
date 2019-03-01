inherit ROOM;
void create()
{
        set("short","清池");
        set("long", @LONG
在這裡你能享受到城內少有的清凈。清池建于南詘年間，後有修
復，在大宋園林工匠的幫助下，更添姿彩。池內魚蝦龜蟲倒也養了不
少，在這四季如春的氣候下，荷花睡蓮無比妖嬈。
LONG );
        set("outdoors", "dali");
        set("exits",([
            "east"  : "/d/dali/sheguta",
        ]));
        set("objects", ([
            //"/kungfu/class/duan/yideng": 1,
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19150);
	set("coor/y", -6880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}