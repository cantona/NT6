// Room: /d/taiwan/riyuetan.c
// Last Modifyed by Ahda on Jan. 4 2002

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "日月潭");
        set("long", @LONG
日月潭位於玉山之北，能高山之南，有龍湖、珠潭、雙潭等稱呼，
生活在此一泓潭水四周的邵族族人則稱其為「水社海」。日月潭之名，
相傳得之於潭中浮島珠仔嶼，以其為界北半形如日輪，南半近似月鈎，
如在水社大山或集集大山上俯瞰，更覺所言不虛。日月潭之美在於它四
周翠峯環抱，湖水碧藍，湖面曲折迤邐，景色優美如畫。日月潭八景：
潭中浮嶼、潭口九曲、萬點漁火、獨木番舟、水社朝霞、荷葉重錢、番
家杵聲、山水拱秀等，遠從清代起，便驚服了文人墨客善感的心。
LONG );
        set("exits", ([
                "northwest" : __DIR__"banxianshe",
        ]));
        set("objects", ([
                __DIR__"npc/shaozhuren": 1,
        ]));
        set("outdoors", "taiwan");
        set("coor/x", 2520);
        set("coor/y", -7010);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
