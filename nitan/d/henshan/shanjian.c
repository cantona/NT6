inherit ROOM;
void create()
{
        set("short", "山澗");
        set("long", @LONG
順山澗漂流而下，沿溪遍布珍稀樹木，泉石，林木，花草及峰巒
均極宜人。澗流至崖折疊飛泄而下，聲震山谷。
LONG );
        set("exits", ([
               "down"     : __DIR__"heishatan",
               "northup"  : __DIR__"fangguangsi",
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6990);
	set("coor/y", -5560);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}