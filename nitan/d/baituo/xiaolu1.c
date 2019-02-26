inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
這裏是一條上山的小路。山路周圍很是僻靜，連個人影也沒有。
往西南是東街，東北處是一塊墳地。
LONG );
        set("outdoors", "baituo");
        set("exits", ([
                "northup"   : __DIR__"xiaolu2",
                "southwest" : __DIR__"dongjie",
                "northeast" : __DIR__"fende",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -49970);
        set("coor/y", 19990);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}