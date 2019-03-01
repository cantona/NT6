// dianwai.c
inherit ROOM;

void create()
{
        set("short", "午門廣場");
        set("long", @LONG
這裡是皇帝廷杖官吏的地方, 也是大將得勝還朝後舉行獻俘禮儀的
場所. 每年十月初一日, 在這裡向全國頒發來年歷書, 時稱“頒朔”.
在內金水河上的五座漢白玉雕橋, 造型秀麗, 同雄偉壯觀的午門城樓和
金碧輝煌的太和門相映, 引人注目. 
LONG
        );
        set("outdoors", "huanggong");
        set("exits", ([
                "east"  : __DIR__"youmen",
                "west"  : __DIR__"zuomen",
                "north" : __DIR__"wumen",
                "south" : "/d/beijing/hgmen_s",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -2800);
	set("coor/y", 7691);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}