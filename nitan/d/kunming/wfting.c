inherit ROOM;

void create()
{
        set("short", "望峯亭");
        set("long", @LONG
這裏是石林最高的一座峯，峯上有一小亭，真不知道是如
何建造出來的，放眼看去，只見四面石峯林立，一時間眼睛都
看花了。
LONG);
        set("outdoors", "kunming");
        set("exits", ([                
                "down" : __DIR__"lianhua",
        ]));
	set("coor/x", -16780);
	set("coor/y", -7200);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}