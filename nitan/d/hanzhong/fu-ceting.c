// fu-ceting 側廳
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "側廳");
        set("long", @LONG
這是正堂旁邊的一間小廳，本來是用作書房的，只是侯員外
家實在找不出多少書來裝點門面，所以就整治成了招待熟客的地
方。廳中擺放着一張八仙桌和幾把椅子，桌上剛沏好的茶還在冒
着熱氣。
LONG
        );
        set("exits", ([
                "west" : __DIR__"fu-datang",
                "north" : __DIR__"fu-huating",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -12230);
	set("coor/y", 780);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}