// Room: /d/fuzhou/xihu.c
// Date: May 12, 98  Java

inherit ROOM;

void create()
{
        set("short", "西湖");
        set("long", @LONG
福州西湖原為灌溉疏濬之利而掘，匯一郭之水以為滋農時。而今，
春水環綠島，長柳戲遊魚，已有十分景致。
LONG );
        set("exits", ([
                "south" : __DIR__"xixiaojie",
        ]));
        set("outdoors", "fuzhou");
        set("no_clean_up", 0);
	set("coor/x", -110);
	set("coor/y", -6170);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}