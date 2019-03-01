// Room: /lingzhou/center.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "城中心");
        set("long", @LONG
這裡是西夏都城靈州的中心廣場，也是四條大街的交匯處，北面是
皇城，南面是商業繁華地段，西面是普通商人區和驃騎營，東面衙門和
王公貴族們的府第。靈州是西域最大的物資集散地和商業中心，也是西
域通往中原的必經之地。各色人等來來往往，馬嘶人喊，熱鬧非凡，廣
場空地上賣藝的、要飯的、大腹便便的財主、提籠攜鳥的王公貴戚到處
都是，偶爾也有行色匆匆的江湖人士一晃而過。
LONG );
        set("exits", ([
                "south" : __DIR__"nandajie",
                "north" : __DIR__"beidajie",
                "east"  : __DIR__"dongdajie",
                "west"  : __DIR__"xidajie",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "lingzhou");
        set("coor/x", -17960);
        set("coor/y", 32070);
        set("coor/z", 0);
        set("coor/x", -6265);
        set("coor/y", 2935);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}