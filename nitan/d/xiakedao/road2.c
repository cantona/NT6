// /d/xiakedao/road2.c 俠客島 山路2
inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
小路曲曲折折地通向山頂，腳步聲驚起一群飛鳥，撲簌簌地消
失在空中。空氣中卻有些腥氣，路邊草叢間不時傳來沙沙的輕響，
可能是毒蛇，還是快點離開的好。
LONG );
        set("outdoors", "xiakedao");
        set("exits", ([
                "southup" : __DIR__"road3",
                "northdown" : __DIR__"road1",
                ]));
        set("objects", ([
                "/d/shenlong/npc/dushe": 2,
        ]));
        set("coor/x", -3000);
        set("coor/y", -22030);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}