inherit ROOM;

void create()
{
        set("short", "後院");
        set("long", @LONG
後院之中綠蔭如雲。許多樹木下設有石凳，供人休息。正中的一
個大鐵香爐中香煙裊裊，許願的人們多有在此磕頭。東面是藏經樓。
西面是千手千眼佛殿。北面是八寶琉璃殿。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"qianshou",
                  "east" : __DIR__"cangjing",
                  "north" : __DIR__"8bao",
                  "south" : __DIR__"daxiong",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5040);
	set("coor/y", 2220);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}