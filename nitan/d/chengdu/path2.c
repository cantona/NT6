// Room: path2.c
// Date: Feb.14 1998 by Java

inherit BUILD_ROOM;
string look_gaoshi();
void create()
{
        set("short", "溪岸小路");
        set("long", @LONG
溪源轉北，陣陣水響帶着你來到草堂前。站在草堂照壁前，回首
浣花溪，想象萬漂墜，少女清歌浣花時節，別是一般滋味。北邊就是
『萬里橋西宅，百花潭北莊』的杜甫草堂了。
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
                "north"  : __DIR__"caotang",
                "south"  : __DIR__"path1",
        ]));
        set("max_room", 4);
        set("no_clean_up", 0);
        set("coor/x", -15270);
	set("coor/y", -1820);
	set("coor/z", 0);
	setup();
}