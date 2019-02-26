// Room: /d/qilian/qilianshan.c
// Winder 2000/09/05 

inherit ROOM;

void create()
{
        set("short", "祁連山");
        set("long", @LONG
祁連山為南祁連山脈的最高峯，海拔五千二百多米，山勢挺拔，為
西北起酒泉，東南至古浪的第一山。山野遍是奇石，為西北一大奇觀，
與東南方馬鬃山遙對。山中據聞時有仙人據石對弈.
LONG );
        set("outdoors", "qilian");
        set("exits", ([
                "southeast" : __DIR__"niaojutai",
                "east"      : __DIR__"mazongshan",
                "west"      : __DIR__"tieshishan",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -12000);
        set("coor/y", 3000);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}