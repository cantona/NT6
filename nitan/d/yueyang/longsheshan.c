// Room: /d/yueyang/longsheshan.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "龍舌山");
        set("long", @LONG
君山地形酷似烏龍臥水，龍涎井前方為龍口，張口向南，兩邊鉗形
山嘴，巖壁拱護，為龍的上、下□，中間的小山為龍舌頭，山勢平舒，
形態逼真，此山因此得名。當年湘妃尋夫至君山，口渴異常。她們的忠
貞感動了洞庭湖中的烏龍。烏龍化著一座小山，張開雙□，伸出舌頭，
讓龍涎滴出，滴在山角下，化成一口古井。湘妃見到古井，飽喝了一頓
井中仙甜的龍涎。頓覺精神振著。湘妃投湖後，烏龍悲傷過度，化為一
座小山，便是這座龍舌山。
LONG );
        set("outdoors", "dongting");
        set("no_clean_up", 0);
        set("exits", ([
                "northdown" : __DIR__"liuyijing",
                "southdown" : __DIR__"feilaizhong",
        ]));
        set("objects", ([
                __DIR__"npc/xiaofan" : 1,
        ]));
        set("coor/x", -1720);
        set("coor/y", 2320);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}