// fu-houyuan.c 後院
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "後院");
        set("long", @LONG
這裡是後院。走到這裡，花香味更加濃烈了。你仔細一看，
東南邊有一道圓形門，似乎花香是從那裡傳出來的。從這裡再往
南走，就是侯員外的臥室了。
LONG
        );
        set("outdoors", "hanzhong");
        set("exits", ([
                "southeast" : __DIR__"houhuayuan",
                "north" : __DIR__"fu-datang",
                "south" : __DIR__"fu-woshi",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -12240);
	set("coor/y", 770);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}