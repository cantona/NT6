// Feb. 6, 1999 by Winder
inherit ROOM;
void create()
{
        set("short", "石室");
        set("long", @LONG
這裡是個不大的石室，有個人盤坐在地上，旁邊點了盞如豆
的油燈，借著這光線，你看見石壁上有幾百幅用利器刻成的簡陋
人形，每個人形均不相同，舉手投足，似在練武。你挨次看去，
密密麻麻都是圖形，心中甚為不解。
LONG
        );
        set("exits", ([
                "up" : __DIR__"shandong7",
 //               "east" : __DIR__"jinshedong1",
        ]));
        set("objects", ([
                __DIR__"npc/jinshe" : 1,
        ]));
        set("coor/x", 1600);
        set("coor/y", -1980);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}